#include "GraphicsOtoHandle.h"
#include "../Modules/WaveformArea.h"

GraphicsOtoHandle::GraphicsOtoHandle(WaveformArea *editor, QGraphicsItem *parent)
    : GraphicsLineHandle(Qt::Horizontal, parent), m_editor(editor) {
    setLineWidth(4);
    setRectWidth(8);

    m_hoverAnimation = new QPropertyAnimation(this, "dynamicLineWidth");
    m_hoverAnimation->setDuration(200);
    m_hoverAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

GraphicsOtoHandle::~GraphicsOtoHandle() {
}

double GraphicsOtoHandle::lineWidth() const {
    return m_lineWidth;
}

void GraphicsOtoHandle::setLineWidth(double lineWidth) {
    m_lineWidth = lineWidth;
    m_dynamicLineWidth = lineWidth;
    update();
}

double GraphicsOtoHandle::rectWidth() const {
    return m_rectWidth;
}

void GraphicsOtoHandle::setRectWidth(double rectWidth) {
    m_rectWidth = rectWidth;
    updateRect();
}

QColor GraphicsOtoHandle::lineColor() const {
    return m_lineColor;
}

void GraphicsOtoHandle::setLineColor(const QColor &lineColor) {
    m_lineColor = lineColor;
    update();
}

void GraphicsOtoHandle::updateRect() {
    setTopLeft(-m_rectWidth / 2, 0);
    setSize(m_rectWidth, m_region.height());
}

QPointF GraphicsOtoHandle::limitArea(QPointF origin) {
    if (origin.x() < m_region.left()) {
        origin.setX(m_region.left());
    } else if (origin.x() > m_region.right()) {
        origin.setX(m_region.right());
    }
    origin.setY(m_region.top());
    return origin;
}

void GraphicsOtoHandle::setRegion(const QRectF &region) {
    m_region = region;

    if (m_region == NO_RECT) {
        hide();
        return;
    } else {
        show();
    }

    setLocation(GraphicsDragger::limitArea(x(), region.top()));
    updateRect();
}

void GraphicsOtoHandle::setPosition(double position) {
    GraphicsLineHandle::setPosition(position);
    emit positionChanged();
}

double GraphicsOtoHandle::dynamicLineWidth() const {
    return m_dynamicLineWidth;
}

void GraphicsOtoHandle::setDynamicLineWidth(double dynamicLineWidth) {
    m_dynamicLineWidth = dynamicLineWidth;
    update();

    emit dynamicLineWidthChanged(m_dynamicLineWidth);
}

void GraphicsOtoHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                              QWidget *widget) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_lineColor);
    painter->drawRect(QRectF(-m_dynamicLineWidth / 2, 0, m_dynamicLineWidth, height()));
}

void GraphicsOtoHandle::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setCursor(QCursor(Qt::PointingHandCursor));

    QPropertyAnimation *a = m_hoverAnimation;
    a->setStartValue(m_lineWidth);
    a->setEndValue(m_rectWidth);
    a->start();
}

void GraphicsOtoHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setCursor(QCursor(Qt::ArrowCursor));

    QPropertyAnimation *a = m_hoverAnimation;
    a->setStartValue(m_rectWidth);
    a->setEndValue(m_lineWidth);
    a->start();
}

void GraphicsOtoHandle::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        linkPress(event->scenePos());
        emit pressed();
    }
}

void GraphicsOtoHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_move) {
        QPointF orgPos = this->pos();
        linkMove(event->scenePos());
        emit moved(pos(), orgPos);
    }
}

void GraphicsOtoHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_moving) {
        linkRelease();
        emit clicked();
    }
}
