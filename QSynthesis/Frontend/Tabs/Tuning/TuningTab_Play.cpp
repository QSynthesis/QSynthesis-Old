#include "Editor/Areas/NotesArea.h"
#include "Editor/EditorForm.h"
#include "Handlers/ProjectInfoHandler.h"
#include "Tracks/TracksInterface.h"
#include "TuningGroup.h"
#include "TuningTab.h"

void TuningTab::play() {
    if (!m_audio) {
        initAudio();
        m_ptrs->editorShell->updatePlayStatus(isPlaying());
    } else {
        stop();
    }
}

void TuningTab::stop() {
    if (m_audio) {
        quitAudio();
    }
    m_ptrs->editorShell->updatePlayStatus(isPlaying());
}

qint64 TuningTab::position() const {
    if (!m_audio) {
        return -1;
    }
    double time = m_startTime + m_audio->processedUSecs() / 1000 - m_audioDelay;
    return qMax(time, m_startTime);
}

void TuningTab::replay() {
    // Obsolete
}

bool TuningTab::isPlaying() const {
    return !!m_audio;
}

void TuningTab::forcePausePlaying() {
    stop();
}
