#ifndef VOLUMEPOINT_H
#define VOLUMEPOINT_H

#include "GraphicsPoint.h"

class EnvelopeHandler;

class VolumePoint : public GraphicsPoint {
public:
    VolumePoint(EnvelopeHandler *scope, NotesArea *editor, QGraphicsItem *parent = nullptr);
    virtual ~VolumePoint();

private:
    void init();

private:
    QPointF limitArea(QPointF origin) override;
    QPointF limitAreaT(QPointF origin) override;
};

#endif // VOLUMEPOINT_H
