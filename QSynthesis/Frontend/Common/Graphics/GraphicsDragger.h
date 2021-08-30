#ifndef GRAPHICSDRAGGER_H
#define GRAPHICSDRAGGER_H

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>

#define qDragOut m_ptrs->draggers
#define qDragIn m_editor->ptrs()->draggers

// Class for objects that can be dragged to move by mouse
class GraphicsDragger : public QGraphicsRectItem {
public:
    explicit GraphicsDragger(QGraphicsItem *parent = nullptr);
    explicit GraphicsDragger(const QRectF &rect, QGraphicsItem *parent = nullptr);
    explicit GraphicsDragger(double x, double y, double w, double h,
                             QGraphicsItem *parent = nullptr);

    virtual ~GraphicsDragger();

    enum Element { Unknown, Note, Point, Lifter, Specific };

    virtual Element element() const;

    bool isToMove() const;
    bool isMoving() const;

    QSizeF size() const;
    double width() const;
    double height() const;

    QPointF topLeft() const;
    double top() const;
    double left() const;

    virtual void setSize(QSizeF size);
    void setSize(double x, double y);
    void setWidth(double w);
    void setHeight(double h);

    virtual void setLocation(QPointF pos);
    void setLocation(double x, double y);
    void setXLocation(double x);
    void setYLocation(double y);

    virtual void setTopLeft(QPointF topLeft);
    void setTopLeft(double left, double top);
    void setLeft(double left);
    void setTop(double top);

    virtual QPointF staticPos() const;
    virtual QSizeF staticSize() const;

    virtual void setInvolved(bool value);
    bool isInvolved() const;
    virtual void setSelected(bool selected);

    void externLimitArea();

    bool operator<(const GraphicsDragger &another) const;

    friend class DraggerHandler;

protected:
    virtual void linkPress(QPointF pos);
    virtual void linkMove(QPointF pos);
    virtual void linkRelease(QPointF pos);
    virtual void linkAbandon();

    virtual void involvePress(QPointF pos);
    virtual void involveMove(QPointF pos);
    virtual void involveRelease(QPointF pos);
    virtual void involveAbandon();

    virtual QPointF limitArea(QPointF p);  // Restrict the region when moving
    virtual QPointF limitAreaT(QPointF p); // Restrict the region when involved
    virtual QSizeF limitSize(QSizeF s);

    QPointF limitArea(double x, double y);
    QPointF limitAreaT(double x, double y);

    virtual void handlePosChange();
    virtual void handleSizeChange();

protected:
    Element m_element;

    bool m_move;
    bool m_moving;

    bool m_involved;

    QSizeF m_windowSize;
    QPointF m_windowPoint, m_startPoint;

    QSizeF m_prevSize;
    QPointF m_prevPoint;

    bool m_sizeChanged;
    bool m_posChanged;

private:
    void init();
};

#endif // GRAPHICSDRAGGER_H
