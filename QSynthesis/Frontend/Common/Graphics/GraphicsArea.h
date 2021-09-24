#ifndef GRAPHICSAREA_H
#define GRAPHICSAREA_H

#include <QEnterEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMoveEvent>
#include <QGraphicsSceneResizeEvent>

class GraphicsArea : public QGraphicsScene {
    Q_OBJECT
public:
    GraphicsArea(QObject *parent = nullptr);
    virtual ~GraphicsArea();

public:
    QPointF mousePos(int index = 0) const;

private:
    virtual bool event(QEvent *event) override;

    virtual void moveEvent(QGraphicsSceneMoveEvent *event);
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);

    virtual void enterEvent(QEnterEvent *event);
    virtual void leaveEvent(QEvent *event);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif // GRAPHICSAREA_H
