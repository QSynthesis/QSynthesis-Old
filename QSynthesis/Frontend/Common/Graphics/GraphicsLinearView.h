#ifndef GRAPHICSLINEARVIEW_H
#define GRAPHICSLINEARVIEW_H

#include <QGraphicsView>
#include <QScrollBar>

class GraphicsLinearView : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphicsLinearView(Qt::Orientation orient, QWidget *parent = nullptr);
    ~GraphicsLinearView();

    Qt::Orientation orient() const;

private:
    Qt::Orientation m_orient;

private:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // GRAPHICSLINEARVIEW_H
