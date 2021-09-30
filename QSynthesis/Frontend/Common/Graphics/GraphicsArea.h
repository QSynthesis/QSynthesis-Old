#ifndef GRAPHICSAREA_H
#define GRAPHICSAREA_H

#include <QEnterEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMoveEvent>
#include <QGraphicsSceneResizeEvent>
#include <QScrollBar>

class GraphicsBaseView;

class GraphicsArea : public QGraphicsScene {
    Q_OBJECT
public:
    explicit GraphicsArea(GraphicsBaseView *view);
    virtual ~GraphicsArea();

public:
    GraphicsBaseView *view() const;
    QPointF mousePos() const;

protected:
    void setVisionFitToItem(QGraphicsItem *item, Qt::AnchorPoint side, bool tween = false);
    void setVisionFitToItem(QGraphicsItem *item, Qt::Orientations orients, bool tween = false);
    void setVisionFitToPos(double pos, Qt::AnchorPoint side, bool tween = false);

protected:
    GraphicsBaseView *m_view;

protected:
    virtual bool event(QEvent *event) override;

    virtual void moveEvent(QGraphicsSceneMoveEvent *event);
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);

    virtual void enterEvent(QEnterEvent *event);
    virtual void leaveEvent(QEvent *event);

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif // GRAPHICSAREA_H
