#ifndef GRAPHICSBASEVIEW_H
#define GRAPHICSBASEVIEW_H

#include <QDebug>
#include <QGraphicsView>
#include <QPropertyAnimation>

class GraphicsArea;

class GraphicsBaseView : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphicsBaseView(QWidget *parent = nullptr);
    explicit GraphicsBaseView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~GraphicsBaseView();

private:
    void init();

public:
    QRectF viewportRect() const;
    GraphicsArea *scene() const;

    void horizontalTween(int value);
    void verticalTween(int value);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void stopTween();

private:
    QRectF m_orgViewportRect;

    QPropertyAnimation *m_horizontalAnimation;
    QPropertyAnimation *m_verticalAnimation;

    bool viewportEvent(QEvent *event) override;
};

#endif // GRAPHICSBASEVIEW_H
