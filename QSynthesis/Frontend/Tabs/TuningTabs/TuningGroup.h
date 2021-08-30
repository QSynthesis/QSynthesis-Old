#ifndef TUNNINGGROUP_H
#define TUNNINGGROUP_H

#include "../TuningTab.h"
#include "Handlers/DraggerHandler.h"

class NotesScrollArea;
class NoneScrollArea;
class LiftersScrollArea;
class QScrollArea;

class TracksForm;
class EditorForm;
class ParamsForm;

class TracksInterface;
class EditorInterface;
class ParamsInterface;

class SectionsArea;
class PianoArea;
class NotesArea;
class HeadsArea;
class BlocksArea;
class LiftersArea;
class ParamsDialArea;

// Save every element's pointer to a group in order to use them in each element
class TuningGroup : public QObject {
    Q_OBJECT

public:
    explicit TuningGroup(TuningTab *parent = nullptr);
    friend QDebug operator<<(QDebug debug, const TuningGroup &tg);

    TuningTab *tab;

    TracksForm *tracksShell;
    EditorForm *editorShell;
    ParamsForm *paramsShell;

    TracksInterface *tracksContent;
    EditorInterface *editorContent;
    ParamsInterface *paramsContent;

    SectionsArea *sectionsArea;
    PianoArea *pianoArea;
    NotesArea *notesArea;

    NoneScrollArea *sectionsScroll;
    NoneScrollArea *pianoScroll;
    NotesScrollArea *notesScroll;

    HeadsArea *trackHeads;
    BlocksArea *trackBlocks;

    NoneScrollArea *headsScroll;
    QScrollArea *blocksScroll;

    LiftersArea *liftersArea;
    ParamsDialArea *dialArea;

    LiftersScrollArea *liftersScroll;

    int currentWidth;  // 15 tick
    int currentHeight; // 1 semitone
    int currentAdsorb;

    int currentSections;

    DraggerHandler draggers;
};

#endif // TUNNINGGROUP_H
