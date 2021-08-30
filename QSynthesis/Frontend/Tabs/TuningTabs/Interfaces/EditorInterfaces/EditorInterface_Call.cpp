#include "../../Areas/Editor/NotesArea.h"
#include "../../Areas/Editor/PianoArea.h"
#include "../../Areas/Editor/SectionsArea.h"
#include "../../Modules/Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"
#include "../EditorInterface.h"

void EditorInterface::adjustCanvas(int totalLength) {
    int sections = totalLength / 480 / 4;
    int count = int((sections + 60) / 40) * 40;

    if (m_ptrs->currentSections != count) {
        m_ptrs->currentSections = count;

        // sectionsArea->setCount(count);
        sectionsArea->adjustWidth();
        notesArea->adjustSize();
    }
}
