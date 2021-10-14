#ifndef DRAGGERHANDLER_H
#define DRAGGERHANDLER_H

#include "Graphics/GraphicsDragger.h"
#include "QUtils.h"
#include "Utils/ItemList.h"

class ScopeHandler;

class GraphicsNote;
class GraphicsPoint;
class GraphicsLifter;

class DraggerHandler : public QObject {
    Q_OBJECT
public:
    DraggerHandler();
    ~DraggerHandler();

    void addOne(GraphicsDragger *obj);
    void removeOne(GraphicsDragger *obj);
    void removeAll(GraphicsDragger::Element element = GraphicsDragger::Unknown);

    void addOneT(GraphicsDragger *obj);
    void removeOneT(GraphicsDragger *obj);
    void removeAllT(GraphicsDragger::Element element = GraphicsDragger::Unknown);

    void addFind(GraphicsNote *p);
    void removeFind(GraphicsNote *p);
    void removeAllFind();

    void startDrag(GraphicsDragger *obj, QPointF pos);
    void duringDrag(GraphicsDragger *obj, QPointF pos);
    void stopDrag(GraphicsDragger *obj);
    void abandonDrag(GraphicsDragger *obj);

    void startInvolve(GraphicsDragger *obj, QPointF pos);
    void duringInvolve(GraphicsDragger *obj, QPointF pos);
    void endInvolve(GraphicsDragger *obj);
    void abandonInvolve(GraphicsDragger *obj);

    GraphicsDragger *rightmost(GraphicsDragger::Element element = GraphicsDragger::Note);
    GraphicsDragger *leftmost(GraphicsDragger::Element element = GraphicsDragger::Note);
    double totalWidth(GraphicsDragger::Element element = GraphicsDragger::Note);

    bool dragging;
    GraphicsDragger *center;

    ItemList<GraphicsNote> selectedNotes; // objects selected or dragged
    ItemList<GraphicsNote> involvedNotes; // non-processing objects involved

    ItemList<GraphicsPoint> selectedPoints; // objects selected or dragged
    ItemList<GraphicsPoint> involvedPoints; // non-processing objects involved

    ItemList<GraphicsLifter> selectedHandles; // objects selected or dragged
    ItemList<GraphicsLifter> involvedHandles; // non-processing objects involved

    ItemList<GraphicsNote> findedNotes;

    void filter(GraphicsDragger::Element element);
    void filter(const QList<GraphicsDragger::Element> &list);

    // Note
public:
    Qs::StretchMode stretching;
    QList<double> possiblePositions;
    ItemList<ScopeHandler> InvolvedScopes;

    double getPossiblePos(double staticX, double x, double w);
    int findPossiblePos(double x);
};

#endif // DRAGGERHANDLER_H
