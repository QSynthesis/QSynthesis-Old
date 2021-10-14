#include "Dialogs/Project/ProjectSettingsDialog.h"
#include "Editor/Areas/NotesArea.h"
#include "Graphics/GraphicsNote.h"
#include "Handlers/ProjectInfoHandler.h"
#include "Operations/ProjectOperation.h"
#include "Tracks/TracksInterface.h"
#include "TuningGroup.h"
#include "TuningTab.h"

void TuningTab::showProjectSettings() {
    if (!isFreeButPlaying()) {
        return;
    }
    forcePausePlaying();
    QString wavtool = projectInfo->wavtool();
    QString outfile = projectInfo->outFile();
    QString cache = relativeCacheDir();

    ProjectSettingsDialog *dlg = new ProjectSettingsDialog(wavtool, outfile, cache, this);

    int code = dlg->exec();
    dlg->deleteLater();

    if (code != 1) {
        return;
    }

    projectInfo->modifyValues(wavtool, outfile);
}

void TuningTab::showCharsetSettings() {
    if (!isFreeButPlaying()) {
        return;
    }
    forcePausePlaying();
}

SectionSettings TuningTab::currentSettings() const {
    SectionSettings sectionSettings;
    // Save from object
    sectionSettings.wavtoolPath = projectInfo->wavtool();
    sectionSettings.outputFileName = projectInfo->outFile();
    sectionSettings.cacheDirectory = relativeCacheDir();

    // Save from track
    sectionSettings.resamplerPath = m_ptrs->tracksContent->defaultResampler();
    sectionSettings.globalFlags = m_ptrs->tracksContent->defaultFlags();
    sectionSettings.projectName = m_ptrs->tracksContent->defaultName();
    sectionSettings.voiceDirectory = m_ptrs->tracksContent->defaultVoiceDir();

    sectionSettings.globalTempo = m_ptrs->notesArea->globalTempo();
    return sectionSettings;
}

void TuningTab::setCurrentSettings(const SectionSettings &sectionSettings) const {
    // Load General Settings To Object
    projectInfo->setWavtool(sectionSettings.wavtoolPath);
    projectInfo->setOutFile(sectionSettings.outputFileName);

    // Load Project Settings To Track
    m_ptrs->tracksContent->setDefaultResampler(sectionSettings.resamplerPath);
    m_ptrs->tracksContent->setDefaultFlags(sectionSettings.globalFlags);
    m_ptrs->tracksContent->setDefaultName(sectionSettings.projectName);
    m_ptrs->tracksContent->setDefaultVoice(sectionSettings.voiceDirectory);

    // Add notes one by one
    m_ptrs->notesArea->setGlobalTempo(sectionSettings.globalTempo);
}
