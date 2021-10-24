#include "../../../Scrolls/NotesScrollArea.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

double NotesArea::tempoAt(int index) const {
    double global = m_globalTempo;
    if (index < 0) {
        return global;
    } else if (index < NotesList.size()) {
        return NotesList.at(index)->tempo();
    } else if (!NotesList.isEmpty()) {
        return NotesList.back()->tempo();
    } else {
        return global;
    }
}

bool NotesArea::getGenonSettings(QString lrc, QGenonSettings *genon, int noteNum) const {
    if (!m_ptrs->tab->oto) {
        return false;
    }
    return m_ptrs->tab->oto->findSample(lrc, genon, noteNum);
}

QPointF NotesArea::convertValueToPosition(int tick, int noteNum) const {
    int curWidth = m_ptrs->currentWidth;
    int curHeight = m_ptrs->currentHeight;

    double toX = double(tick) / 480 * curWidth + zeroLine(); // -1 section is the leftmost
    double toY = curHeight * (107 - noteNum);

    return QPointF(toX, toY);
}

QRectF NotesArea::convertValueToGeometry(int tick, int noteNum, int length) const {
    int curWidth = m_ptrs->currentWidth;
    int curHeight = m_ptrs->currentHeight;

    QPointF p = convertValueToPosition(tick, noteNum);
    double toW = double(length) / 480 * double(curWidth);
    double toH = curHeight;

    return QRectF(p.x(), p.y(), toW, toH);
}

QPair<int, int> NotesArea::convertPositionToValue(QPointF pos) const {
    int curWidth = m_ptrs->currentWidth;
    int curHeight = m_ptrs->currentHeight;

    int tick = (pos.x() - zeroLine()) / curWidth * 480;
    int noteNum = 107 - int(pos.y() / curHeight);

    return qMakePair(tick, noteNum);
}

double NotesArea::convertWidthToLength(int width) const {
    int curWidth = m_ptrs->currentWidth;
    return double(width) / curWidth * 480;
}

double NotesArea::convertTickToTime(int tick) const {
    if (tick >= totalLength()) {
        return -1;
    }
    int index = findNoteAtTick(tick);
    GraphicsNote *p = NotesList.at(index);
    double unit = 120.0 / p->tempo() / 0.96;
    return p->time() + (tick - p->tick()) * unit;
}

int NotesArea::findNoteAtPos(double x) const {
    int i = 0;
    int j = NotesList.size() - 1;
    int mid;

    while (i <= j) {
        mid = i + (j - i) / 2;
        if (NotesList.at(mid)->x() + NotesList.at(mid)->width() < x) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }

    return i;
}

int NotesArea::findNoteAtPosAbs(double x) const {
    if (x < zeroLine() || NotesList.isEmpty()) {
        return -1;
    }
    if (x > NotesList.back()->tailPos().x()) {
        return NotesList.size();
    }
    return findNoteAtPos(x);
}

QPoint NotesArea::viewportNotesRange() const {
    QRectF vp = viewportRect();

    if (NotesList.isEmpty()) {
        return QPoint(-1, -1);
    }

    int aIndex = findNoteAtPos(vp.left());
    int bIndex = findNoteAtPos(vp.right());

    if (bIndex >= NotesList.size()) {
        bIndex = NotesList.size() - 1;
    }
    return QPoint(aIndex, bIndex);
}

int NotesArea::findNoteAtTick(int x) const {
    int i = 0;
    int j = NotesList.size() - 1;
    int mid;

    while (i <= j) {
        mid = i + (j - i) / 2;
        if (NotesList.at(mid)->tick() + NotesList.at(mid)->Note.length < x) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }

    return i;
}

int NotesArea::findNoteAtTime(double x) const {
    int i = 0;
    int j = NotesList.size() - 1;
    int mid;

    while (i <= j) {
        mid = i + (j - i) / 2;
        if (NotesList.at(mid)->time() + NotesList.at(mid)->duration() < x) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }

    return i;
}

QRectF NotesArea::viewportRect() const {
    return view()->viewportRect();
}
