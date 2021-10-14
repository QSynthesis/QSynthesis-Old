#ifndef GRAPHICSPLANEHANDLE_H
#define GRAPHICSPLANEHANDLE_H

#include "GraphicsHandle.h"

class GraphicsPlaneHandle : public GraphicsHandle {
public:
    explicit GraphicsPlaneHandle(QGraphicsItem *parent = nullptr);
    virtual ~GraphicsPlaneHandle();

private:
    void init();

public:
    void setValue(QPointF values);

    void setValueX(double value);
    void setValueY(double value);

    QPointF value() const;

    double valueX() const;
    double valueY() const;
};

#endif // GRAPHICSPLANEHANDLE_H
