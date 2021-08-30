#include "LinearScrollArea.h"

LinearScrollArea::LinearScrollArea(Qt::Orientation ori, QWidget *parent)
    : QScrollArea(parent), m_orient(ori) {
    if (ori == Qt::Horizontal) {
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        verticalScrollBar()->setEnabled(false);
    } else {
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        horizontalScrollBar()->setEnabled(false);
    }
}

Qt::Orientation LinearScrollArea::orient() const {
    return m_orient;
}

void LinearScrollArea::resizeEvent(QResizeEvent *event) {
    QWidget *w = widget();
    if (!w) {
        return;
    }

    if (m_orient == Qt::Horizontal) {
        if (w->height() != viewport()->height()) {
            w->setFixedHeight(viewport()->height());
        }
    } else {
        if (w->width() != viewport()->width()) {
            w->setFixedWidth(viewport()->width());
        }
    }

    QScrollArea::resizeEvent(event);
}
