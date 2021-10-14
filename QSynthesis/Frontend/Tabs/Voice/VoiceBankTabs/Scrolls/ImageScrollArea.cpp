#include "ImageScrollArea.h"

#include <QApplication>
#include <QDebug>
#include <QMouseEvent>

ImageScrollArea::ImageScrollArea(QWidget *parent) : QScrollArea(parent) {
    viewport()->installEventFilter(this);
}

ImageScrollArea::~ImageScrollArea() {
}

bool ImageScrollArea::eventFilter(QObject *obj, QEvent *event) {
    if (obj == viewport() && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
       QWidget *w = widget();
        if (w) {
            QApplication::sendEvent(w, mouseEvent);
            return true;
        }
    }
    return QScrollArea::eventFilter(obj, event);
}
