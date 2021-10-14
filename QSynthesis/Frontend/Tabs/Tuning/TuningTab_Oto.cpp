#include "Editor/Areas/NotesArea.h"
#include "Handlers/ProjectInfoHandler.h"
#include "Tracks/Areas/HeadsArea.h"
#include "TuningGroup.h"
#include "TuningTab.h"

void TuningTab::switchToOtoReferenceMap(const QString &voiceDir) {
    if (oto) {
        if (oto->voiceDir() == voiceDir) {
            return;
        }
        disconnect(oto, &QOtoReference::refresh, this, &TuningTab::handleOtoRefreshed);
        QOtoReference::removeReference(oto->voiceDir());
        oto = nullptr;
    }
    if (!voiceDir.isEmpty()) {
        QOtoReference::addReference(voiceDir, oto);
        connect(oto, &QOtoReference::refresh, this, &TuningTab::handleOtoRefreshed);
    }
    handleOtoRefreshed();
}

void TuningTab::handleOtoRefreshed() {
    m_ptrs->notesArea->updateNotesStatus();
    m_ptrs->notesArea->adjustNoteComponents();
    m_ptrs->notesArea->reloadSprite();
}
