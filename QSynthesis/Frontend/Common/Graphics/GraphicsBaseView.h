#ifndef GRAPHICSBASEVIEW_H
#define GRAPHICSBASEVIEW_H

#include <QDebug>
#include <QGraphicsView>

class GraphicsArea;

class GraphicsBaseView : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphicsBaseView(QWidget *parent = nullptr);
    explicit GraphicsBaseView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~GraphicsBaseView();

    QRectF viewportRect() const;
    GraphicsArea *scene() const;

private:
    QRectF m_orgViewportRect;

    bool viewportEvent(QEvent *event) override;
};

#endif // GRAPHICSBASEVIEW_H
