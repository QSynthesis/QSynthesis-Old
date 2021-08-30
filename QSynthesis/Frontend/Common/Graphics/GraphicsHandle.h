#ifndef GRAPHICSHANDLE_H
#define GRAPHICSHANDLE_H

#include "GraphicsDragger.h"

class GraphicsHandle : public GraphicsDragger {
public:
    explicit GraphicsHandle(QGraphicsItem *parent = nullptr);
    virtual ~GraphicsHandle();

private:
    void init();

public:
    QRectF region() const;
    virtual void setRegion(const QRectF &region);

protected:
    QRectF m_region;

private:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // GRAPHICSHANDLE_H
