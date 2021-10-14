#ifndef MOREPOINT_H
#define MOREPOINT_H

#include <QPointF>

class MorePoint : public QPointF {
public:
    MorePoint();
    MorePoint(const QPoint &p);
    MorePoint(const QPointF &p);
    MorePoint(qreal xpos, qreal ypos);
    virtual ~MorePoint();
};

#endif // MOREPOINT_H
