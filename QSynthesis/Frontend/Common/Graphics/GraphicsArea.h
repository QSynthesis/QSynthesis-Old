#ifndef GRAPHICSAREA_H
#define GRAPHICSAREA_H

#include <QGraphicsScene>

class GraphicsArea : public QGraphicsScene {
public:
    GraphicsArea(QObject *parent = nullptr);
    virtual ~GraphicsArea();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif // GRAPHICSAREA_H
