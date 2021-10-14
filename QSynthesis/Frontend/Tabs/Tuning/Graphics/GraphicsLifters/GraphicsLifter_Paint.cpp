#include "../GraphicsLifter.h"

void GraphicsLifter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
    QPen pen(m_active ? (m_highlighted ? m_activeHColor : m_activeColor)
                      : (m_highlighted ? m_inactiveHColor : m_inactiveColor),
             3);

    double radius = Radius - pen.widthF();

    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    painter->drawEllipse(QPointF(0, 0), radius, radius);
    painter->drawLine(QPointF(radius, 0), QPointF(width() - radius, 0));
    painter->drawLine(QPointF(0, radius), QPointF(0, m_geometry.height()));
}

QRectF GraphicsLifter::boundingRect() const {
    return m_geometry;
}
