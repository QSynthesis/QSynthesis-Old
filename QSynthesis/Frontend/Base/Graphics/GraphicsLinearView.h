#ifndef GRAPHICSLINEARVIEW_H
#define GRAPHICSLINEARVIEW_H

#include <QScrollBar>

#include "Graphics/GraphicsBaseView.h"

class GraphicsLinearView : public GraphicsBaseView {
    Q_OBJECT
public:
    explicit GraphicsLinearView(Qt::Orientation orient,QWidget *parent = nullptr);
    ~GraphicsLinearView();

    Qt::Orientation orient() const;

private:
    Qt::Orientation m_orient;

private:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // GRAPHICSLINEARVIEW_H
