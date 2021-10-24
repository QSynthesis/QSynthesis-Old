#include "GraphicsBar.h"

#include <QPainter>
#include <QPen>

GraphicsBar::GraphicsBar(QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    m_barColor = Qt::green;
}

GraphicsBar::~GraphicsBar() {
}

void GraphicsBar::setVisibleLines(const QList<QPair<int, int>> &pairs) {
    m_lines = pairs;
    update();
}

QColor GraphicsBar::barColor() const {
    return m_barColor;
}

void GraphicsBar::setBarColor(const QColor &barColor) {
    m_barColor = barColor;
}

QPainterPath GraphicsBar::shape() const {
    return QPainterPath();
}

void GraphicsBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(m_barColor));
    for (auto it = m_lines.begin(); it != m_lines.end(); ++it) {
        painter->drawRect(QRectF(it->first, 0, it->second, rect().height()));
    }
}
