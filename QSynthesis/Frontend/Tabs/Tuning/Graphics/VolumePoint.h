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
    MorePoint limitArea(MorePoint origin) override;
    MorePoint limitAreaT(MorePoint origin) override;
};

#endif // VOLUMEPOINT_H
