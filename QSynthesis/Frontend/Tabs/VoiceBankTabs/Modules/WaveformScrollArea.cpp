#include "WaveformScrollArea.h"

#include <QEvent>

WaveformScrollArea::WaveformScrollArea(QWidget *parent)
    : GraphicsLinearView(Qt::Horizontal, parent) {
    setAlignment(Qt::AlignLeft);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    verticalScrollBar()->installEventFilter(this);
    horizontalScrollBar()->installEventFilter(this);
}

WaveformScrollArea::~WaveformScrollArea() {
}

QRectF WaveformScrollArea::viewportRect() const {
    QRect viewport_rect(0, 0, viewport()->width(), viewport()->height());
    QRectF visible_scene_rect = mapToScene(viewport_rect).boundingRect();
    return visible_scene_rect;
}

bool WaveformScrollArea::eventFilter(QObject *obj, QEvent *event) {
    if (obj == verticalScrollBar() || obj == horizontalScrollBar()) {
        if (event->type() == QEvent::Wheel) {
            return true;
        }
    }
    // pass the event on to the parent class
    return QGraphicsView::eventFilter(obj, event);
}
