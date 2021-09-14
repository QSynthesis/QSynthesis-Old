#ifndef GRAPHICSPOINT_H
#define GRAPHICSPOINT_H

#include "Graphics/GraphicsDragger.h"
#include "QControlPoint.h"
#include "QUtils.h"

class NotesArea;
class ScopeHandler;

class GraphicsPoint : public GraphicsDragger {
public:
    explicit GraphicsPoint(ScopeHandler *scope, NotesArea *editor, QGraphicsItem *parent = nullptr);
    virtual ~GraphicsPoint();

    enum Line { EaseIn, EaseOut, Peak, Valley, Center };

    QControlPoint TPoint;

    friend class DraggerHandler;

private:
    void init();

    // Properties
public:
    Qs::SpecialPos specialPos() const;
    bool setSpecialPos(Qs::SpecialPos specialPos);

    double generalX() const;
    double generalY() const;

    double absoulteY() const;

    ScopeHandler *scope() const;

public:
    void setHovered(bool hovered);
    bool hovered() const;

    double radius() const;

    bool drawing() const;
    void setDrawing(bool drawing);

    Qs::SpecialPos staticSpecialPos() const;

protected:
    NotesArea *m_editor;
    ScopeHandler *m_scope;

    bool m_hovered;
    double m_radius;
    bool m_drawing;

    Qs::SpecialPos m_specialPos;
    Qs::SpecialPos m_windowSpecialPos;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

public:
    void afterPress();
    void afterMove(QPointF pos);
    void afterRelease();
    void autoRelease();

private:
    MorePoint limitArea(MorePoint origin) override;
    MorePoint limitAreaT(MorePoint origin) override;

    void involvePress(QPointF pos) override;
    void linkPress(QPointF pos) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
};

#endif // GRAPHICSPOINT_H
