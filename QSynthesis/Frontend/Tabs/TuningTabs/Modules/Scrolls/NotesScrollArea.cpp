#include "NotesScrollArea.h"

#include <QEvent>
#include <QScrollBar>

NotesScrollArea::NotesScrollArea(QWidget *parent) : QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);

    viewMenu = new QMenu(this);

    verticalScrollBar()->installEventFilter(this);
    horizontalScrollBar()->installEventFilter(this);
}

NotesScrollArea::~NotesScrollArea() {
}

QRectF NotesScrollArea::viewportRect() const {
    QRect viewport_rect(0, 0, viewport()->width(), viewport()->height());
    QRectF visible_scene_rect = mapToScene(viewport_rect).boundingRect();
    return visible_scene_rect;
}

bool NotesScrollArea::eventFilter(QObject *obj, QEvent *event) {
    if (obj == verticalScrollBar() || obj == horizontalScrollBar()) {
        if (event->type() == QEvent::Wheel) {
            return true;
        }
    }
    // pass the event on to the parent class
    return QGraphicsView::eventFilter(obj, event);
}
