#ifndef GRAPHICSBAR_H
#define GRAPHICSBAR_H

#include <QGraphicsRectItem>

class GraphicsBar : public QGraphicsRectItem {
public:
    explicit GraphicsBar(QGraphicsItem *parent = nullptr);
    ~GraphicsBar();

public:
    void setVisibleLines(const QList<QPair<int, int>> &pairs);

    QColor barColor() const;
    void setBarColor(const QColor &barColor);

private:
    QColor m_barColor;
    QList<QPair<int, int>> m_lines;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
};

#endif // GRAPHICSBAR_H
