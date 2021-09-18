#include "VibratoPlaneHandle.h"
#include "../../Areas/Editor/NotesArea.h"
#include "../../Handlers/Mode2Handler.h"
#include "../../Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"
#include "QUtils.h"

VibratoPlaneHandle::VibratoPlaneHandle(NotesArea *editor, Mode2Handler *scope,
                                       QGraphicsItem *parent)
    : VibratoObject(editor, scope), GraphicsPlaneHandle(parent) {
    init();
}

VibratoPlaneHandle::~VibratoPlaneHandle() {
}

void VibratoPlaneHandle::updateColorTheme() {
    m_borderColor = qViewIn->vbrPlaneHandleBorder();
    m_fillColor = qViewIn->vbrPlaneHandleFill();
    m_textColor = qViewIn->vbrPlaneHandleText();

    update();
}

void VibratoPlaneHandle::init() {
    m_region = NO_RECT;

    m_borderColor = Qt::black;
    m_fillColor = Qt::white;
    m_textColor = Qt::black;
    m_ringWidth = 1.5;

    updateColorTheme();
    connect(qViewIn, &NotesScrollArea::vbrHandleThemeUpdated, this,
            &VibratoPlaneHandle::updateColorTheme);
}

double VibratoPlaneHandle::padding() const {
    return m_padding;
}

void VibratoPlaneHandle::setPadding(double padding) {
    m_padding = padding;
    update();
}

double VibratoPlaneHandle::ringWidth() const {
    return m_ringWidth;
}

void VibratoPlaneHandle::setRingWidth(double ringWidth) {
    m_ringWidth = ringWidth;
    update();
}

QColor VibratoPlaneHandle::fillColor() const {
    return m_fillColor;
}

void VibratoPlaneHandle::setFillColor(const QColor &fillColor) {
    m_fillColor = fillColor;
    update();
}

QColor VibratoPlaneHandle::textColor() const {
    return m_textColor;
}

void VibratoPlaneHandle::setTextColor(const QColor &textColor) {
    m_textColor = textColor;
    update();
}

QColor VibratoPlaneHandle::borderColor() const {
    return m_borderColor;
}

void VibratoPlaneHandle::setBorderColor(const QColor &borderColor) {
    m_borderColor = borderColor;
    update();
}

QString VibratoPlaneHandle::text() const {
    return m_text;
}

void VibratoPlaneHandle::setText(const QString &text) {
    m_text = text;
    update();
}

MorePoint VibratoPlaneHandle::limitArea(MorePoint origin) {
    if (m_region == NO_RECTF) {
        return origin;
    }

    if (origin.x() < m_region.left()) {
        origin.setX(m_region.left());
    } else if (origin.x() > m_region.right()) {
        origin.setX(m_region.right());
    }

    if (origin.y() < m_region.top()) {
        origin.setY(m_region.top());
    } else if (origin.y() > m_region.bottom()) {
        origin.setY(m_region.bottom());
    }

    return origin;
}

void VibratoPlaneHandle::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDragIn.removeAll();
    emit pressed();
}

void VibratoPlaneHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        afterMove(event->scenePos());
    }
}

void VibratoPlaneHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    afterRelease();
}

void VibratoPlaneHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    GraphicsPlaneHandle::hoverLeaveEvent(event);
    if (m_move) {
        afterRelease();
    }
}

void VibratoPlaneHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                               QWidget *widget) {
    double radius = rect().width() / 2 - m_padding;
    double inRadius = rect().width() / 2 - m_padding - m_ringWidth;

    painter->setPen(Qt::NoPen);

    painter->setBrush(m_borderColor);
    painter->drawEllipse(QPointF(0, 0), radius, radius);

    painter->setBrush(m_fillColor);
    painter->drawEllipse(QPointF(0, 0), inRadius, inRadius);

    painter->setPen(m_textColor);
    painter->setBrush(Qt::NoBrush);
    painter->setFont(uiFont());
    painter->drawText(rect(), Qt::AlignCenter, m_text);
}

void VibratoPlaneHandle::afterPress() {
}

void VibratoPlaneHandle::afterMove(QPointF pos) {
    if (!m_move) {
        linkPress(pos);
        emit pressed();
    }
    if (m_move) {
        linkMove(pos);
        emit moved();
    }
}

void VibratoPlaneHandle::afterRelease() {
    if (m_move) {
        linkRelease();
        emit clicked();
    }
}
