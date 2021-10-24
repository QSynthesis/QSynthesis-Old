#include "../../../TuningGroup.h"
#include "../../../TuningTab.h"
#include "../NotesArea.h"

void NotesArea::initBarModules() {
    bar = new GraphicsBar();
    addItem(bar);
    bar->setZValue(barZIndex);
}

void NotesArea::updateBar() {
    QRectF vp = viewportRect();
    bar->setPos(vp.x(), vp.y());
    bar->setRect(0, 0, vp.width(), 2);

    QPoint range = viewportNotesRange();
    if (range.x() < 0) {
        bar->setVisibleLines({});
        return;
    }

    QList<QPair<int, int>> pairs;
    int prev = -2;
    for (int i = range.x(); i <= range.y(); ++i) {
        GraphicsNote *p = NotesList.at(i);
        double x = p->x() - bar->x();
        double w = p->width();

        if (m_ptrs->tab->isRendered(i)) {
            if (i == prev + 1) {
                pairs.back().second += w;
            } else {
                pairs.append(qMakePair(x, w));
            }
            prev = i;
        }
    }
    bar->setVisibleLines(pairs);
}

void NotesArea::reloadBar() {
    updateBar();
}
