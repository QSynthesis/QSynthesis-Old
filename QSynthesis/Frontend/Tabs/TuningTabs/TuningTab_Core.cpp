#include "../TuningTab.h"

#include "Areas/Editor/NotesArea.h"
#include "Interfaces/TracksInterface.h"
#include "ProjectInfoHandler.h"
#include "TuningGroup.h"
#include "mainwindow.h"

bool TuningTab::load() {
    bool aResult;
    bool aValid;

    ustFile.setFilename(m_filename);
    aResult = ustFile.load(&aValid);
    if (!aResult) {
        if (aValid) {
            // Query file failed
            QMessageBox::warning(this, MainTitle, tr("Unable to open file!"));
        } else {
            // The format is invalid
            QMessageBox::warning(this, MainTitle, tr("Invalid format!"));
        }
        ustFile.reset();
    }
    loadCore();
    return aResult;
}

bool TuningTab::save() {
    return saveOrSaveAs("");
}

bool TuningTab::saveAs(const QString &filename) {
    return saveOrSaveAs(filename);
}

bool TuningTab::restore() {
    clearHistory();
    setEdited(false);
    loadCore();
    return true;
}

void TuningTab::awake() {
    CentralTab::awake();
}

void TuningTab::sleep() {
    CentralTab::sleep();
}

void TuningTab::enter() {
    CentralTab::enter();
}

void TuningTab::leave() {
    CentralTab::leave();
    forcePausePlaying();
}

void TuningTab::newFile(const SectionNotes &notes) {
    if (!notes.isEmpty()) {
        ustFile.sectionSettings().globalTempo = notes.initTempo();
        ustFile.setSectionNotes(notes);
        savedHistoryIndex = -1;
        setEdited(true);
    }
    loadCore();
}

void TuningTab::appendFile(const SectionNotes &notes) {
    if (notes.isEmpty()) {
        return;
    }
    QVector<QLinkNote> newNotes = notes;
    m_ptrs->notesArea->pasteNotes(newNotes.toList());
    change();
}

void TuningTab::loadCore() {
    qDebug() << "[Load UST]"
             << "Add notes from ust file.";

    setCurrentSettings(ustFile.sectionSettings());
    m_ptrs->notesArea->inputNotes(ustFile.sectionNotes().toList());
    m_ptrs->notesArea->centralizeVision(0);

    renderBefore();
}

void TuningTab::saveCore() {
    qDebug() << "[Save UST]"
             << "Replace notes with GUI notes.";

    QVector<QLinkNote> notes = m_ptrs->notesArea->allNotes().toVector();
    ustFile.setSectionVersion(SectionVersion());
    ustFile.setSectionSettings(currentSettings());
    ustFile.setSectionNotes(notes);
}

void TuningTab::exitCore() {
    switchToOtoReferenceMap("");
    if (edited) {
        removeAllCaches();
    }
}

bool TuningTab::saveOrSaveAs(const QString &filename) {
    bool saveAs = !filename.isEmpty();

    SequenceTextFile orgFile;
    orgFile.setFilename(ustFile.filename());
    orgFile.setSectionVersion(ustFile.sectionVersion());
    orgFile.setSectionSettings(ustFile.sectionSettings());
    orgFile.setSectionNotes(ustFile.sectionNotes());

    if (saveAs) {
        ustFile.setFilename(filename);
    }
    saveCore(); // Replace

    bool aResult = ustFile.save();

    if (!aResult) {
        // No permission granted to write file
        QMessageBox::warning(this, MainTitle, tr("Unable to write file!"));

        // restore
        if (saveAs) {
            ustFile.setFilename(orgFile.filename());
        }
        ustFile.setSectionVersion(orgFile.sectionVersion());
        ustFile.setSectionSettings(orgFile.sectionSettings());
        ustFile.setSectionNotes(orgFile.sectionNotes());
    } else {
        deleted = false;
        untitled = false;
        setEdited(false);
        savedHistoryIndex = historyIndex; // Update saved history index
    }

    return aResult;
}

bool TuningTab::saveTempFile() {
    QString tempUSTName = "temp$$$.ust";
    QString tempFileName = m_workingDir + Slash + tempUSTName;

    qDebug() << "[I/O]"
             << "Save Temp File at" << tempFileName;

    SequenceTextFile ust(tempFileName);

    ust.setSectionVersion(SectionVersion());
    ust.setSectionSettings(currentSettings());
    ust.setSectionNotes(m_ptrs->notesArea->allNotes().toVector());

    return ust.save();
}
