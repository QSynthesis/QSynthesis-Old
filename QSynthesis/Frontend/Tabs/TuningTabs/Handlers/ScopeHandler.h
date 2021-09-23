#ifndef SCOPEHANDLER_H
#define SCOPEHANDLER_H

#include "QControlPoint.h"
#include "QUtils.h"
#include "Utils/ItemList.h"

class GraphicsNote;
class GraphicsPoint;
class GraphicsLines;
class NotesArea;

class ScopeHandler : public QObject {
    Q_OBJECT
public:
    explicit ScopeHandler();
    explicit ScopeHandler(GraphicsNote *note, NotesArea *editor);
    virtual ~ScopeHandler();

    Qs::Scope type() const;

    ItemList<GraphicsPoint> Points;

    bool operator<(const ScopeHandler &another) const;

private:
    void init();

    // Variate
public:
    virtual void fromNotePoints();
    virtual void toNotePoints();

    void removeAllPoints();

    virtual GraphicsPoint *insertPoint(QPointF pos);

    virtual void replacePoints(const QList<QControlPoint> &arr);
    virtual bool removePoints(const QList<GraphicsPoint *> &points);
    virtual void clearPoints();

    virtual void makeDefaultPoints();

    // Properties
public:
    GraphicsNote *note() const;
    void setNote(GraphicsNote *note);

    NotesArea *editor() const;
    void setEditor(NotesArea *editor);

    GraphicsLines *screen() const;

    GraphicsNote *prevNote() const;
    GraphicsNote *nextNote() const;

    GraphicsPoint *firstPoint() const; // Return the leftmost point (NULL if no points)
    GraphicsPoint *lastPoint() const;  // Return the rightmost point (NULL if no points)

    bool solid() const;
    bool visible() const;

    // States
public:
    void update();

    void setPointsVisible(bool value);
    QPoint selectContinuously(bool selectAll = false);

    virtual void setSolid(bool solid);
    virtual void setVisible(bool visible);

    virtual void adjustGeometry();
    virtual void adjustPoints();
    virtual void limitAllPoints();

    // Methods for handle
    bool updateXRank();

    // Move
public:
    virtual void prepareMove(GraphicsPoint *p);
    virtual void refreshMove(GraphicsPoint *p);
    virtual void endMove(GraphicsPoint *p);

    // Assist
public:
    virtual QRectF activeScope() const;
    virtual QRectF visionScope() const;

    virtual GraphicsPoint *getNearestPoint(GraphicsPoint *p, int limitedPos) const;

    virtual double convertPosToValueX(double x) const;
    virtual double convertPosToValueY(double y) const;

    virtual double convertValueToPosX(double x) const;
    virtual double convertValueToPosY(double y) const;

    QPoint continuousSelection() const;

public:
    virtual void drawPoint(QPainter *painter, GraphicsPoint *p);

protected:
    Qs::Scope m_type;
    bool m_moving;

    GraphicsNote *m_note;
    NotesArea *m_editor;

    bool m_solid;
    bool m_visible;

    QRectF m_geometry;
    QRectF m_activeScope;

    void insertSort();

    // Core
protected:
    virtual GraphicsPoint *createPointCore();
    virtual void removePointCore(GraphicsPoint *p);
};

#endif // SCOPEHANDLER_H
