#include "../TuningTab.h"
#include "Areas/Editor/NotesArea.h"
#include "Dialogs/ProjectSettingsDialog.h"
#include "Graphics/GraphicsNote.h"
#include "Interfaces/TracksInterface.h"
#include "Operations/ProjectOperation.h"
#include "ProjectInfoHandler.h"
#include "TuningGroup.h"

void TuningTab::showProjectSettings() {
    if (isPlaying()) {
        return;
    }
    QString wavtool = projectInfo->wavtool();
    QString outfile = projectInfo->outFile();
    QString cache = relativeCacheDir();

    ProjectSettingsDialog *dlg = new ProjectSettingsDialog(wavtool, outfile, cache);

    int code = dlg->exec();
    dlg->deleteLater();

    if (code != 1) {
        return;
    }

    projectInfo->modifyValues(wavtool, outfile);
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
