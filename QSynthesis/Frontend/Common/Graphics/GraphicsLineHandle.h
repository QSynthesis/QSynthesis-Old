#ifndef GRAPHICSLINEHANDLE_H
#define GRAPHICSLINEHANDLE_H

#include "GraphicsHandle.h"

class GraphicsLineHandle : public GraphicsHandle {
public:
    explicit GraphicsLineHandle(Qt::Orientation orient, QGraphicsItem *parent = nullptr);
    virtual ~GraphicsLineHandle();

private:
    void init();

public:
    Qt::Orientation orient() const;

    double value() const;
    virtual void setValue(double value);

    double position() const;
    virtual void setPosition(double position);

protected:
    Qt::Orientation m_orient;
};

#endif // GRAPHICSLINEHANDLE_H
