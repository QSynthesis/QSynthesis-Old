#ifndef GRAPHICSPLAYHEAD_H
#define GRAPHICSPLAYHEAD_H

#include <QGraphicsRectItem>

class GraphicsPlayHead : public QGraphicsRectItem {
public:
    explicit GraphicsPlayHead(QGraphicsItem *parent =nullptr);
    ~GraphicsPlayHead();

public:
    double left() const;
    double right() const;

private:
    QPainterPath shape() const override;
};

#endif // GRAPHICSPLAYHEAD_H
