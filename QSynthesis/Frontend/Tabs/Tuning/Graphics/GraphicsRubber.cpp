#include "GraphicsRubber.h"
#include "../Editor/Areas/NotesArea.h"
#include "../Scrolls/NotesScrollArea.h"

#include <QDebug>
#include <QGraphicsScene>

GraphicsRubber::GraphicsRubber(NotesArea *editor, QGraphicsItem *parent)
    : QGraphicsRectItem(parent), m_editor(editor) {
    init();
    setStartPoint(QPoint(0, 0));
}

GraphicsRubber::~GraphicsRubber() {
}

void GraphicsRubber::updateColorTheme() {
    m_frameColor = qViewIn->rubberFrame();
    m_fillColor = qViewIn->rubberFill();
    update();
}

void GraphicsRubber::init() {
    m_active = false;
    m_vertical = false;

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GraphicsRubber::onTimer);

    updateColorTheme();
    connect(qViewIn, &NotesScrollArea::rubberThemeUpdated, this, &GraphicsRubber::updateColorTheme);
}

void GraphicsRubber::setStartPoint(QPointF pos) {
    m_start = pos;
    setEndPoint(pos + QPointF(1, 1));
}

void GraphicsRubber::setEndPoint(QPointF pos) {
    m_end = pos;

    int m_left = qMin(m_start.x(), m_end.x());
    int m_width = qAbs(m_start.x() - m_end.x());
    int m_top = qMin(m_start.y(), m_end.y());
    int m_height = qAbs(m_start.y() - m_end.y());

    prepareGeometryChange();
    if (m_vertical) {
        setPos(m_left, 0);
        setRect(0, 0, m_width, scene()->sceneRect().height());
    } else {
        setPos(m_left, m_top);
        setRect(0, 0, m_width, m_height);
    }
}

bool GraphicsRubber::active() const {
    return m_active;
}

void GraphicsRubber::setActive(bool active) {
    m_active = active;

    if (active) {
        m_timer->start(10);
    } else {
        m_timer->stop();
    }

    setVisible(active);
}

QColor GraphicsRubber::frameColor() const {
    return m_frameColor;
}

void GraphicsRubber::setFrameColor(const QColor &frameColor) {
    m_frameColor = frameColor;
    update();
}

QColor GraphicsRubber::fillColor() const {
    return m_fillColor;
}

void GraphicsRubber::setFillColor(const QColor &fillColor) {
    m_fillColor = fillColor;
    update();
}

bool GraphicsRubber::vertical() const {
    return m_vertical;
}

void GraphicsRubber::setVertical(bool vertical) {
    m_vertical = vertical;
}

void GraphicsRubber::onTimer() {
    emit selecting();
}

void GraphicsRubber::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
    painter->setPen(QPen(m_frameColor, 1));
    painter->setBrush(m_fillColor);

    QRectF rect = this->rect();
    rect.adjust(1, 1, -1, -1);

    painter->drawRect(rect);
}

void GraphicsRubber::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    emit selectOver();
}

void GraphicsRubber::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit selectOver();
}
