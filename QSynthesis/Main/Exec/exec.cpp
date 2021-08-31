#include "mainwindow.h"

bool MainWindow::execOpen() {
    QStringList paths = QFileDialog::getOpenFileNames(this, tr("Open File"), ".", openFilterString);
    if (!paths.isEmpty()) {
        return addMultipleTabs(paths);
    } else {
        return false;
    }
}

bool MainWindow::execOpenFolder() {
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Voice Bank"));
    if (!path.isEmpty()) {
        return addVoiceBankTab(path);
    } else {
        return false;
    }
}

bool MainWindow::execSave(CentralTab *tab) {
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        if (tab1->isDeleted() || tab1->isUntitled()) {
            return execSaveAs(tab1);
        }
    } else if (tab->tabType() == Qs::Keyboard) {
        KeyboardTab *tab1 = qobject_cast<KeyboardTab *>(tab);
        bool res = tab1->save();
        if (res) {
            shortcuts = tab1->keys;
            reloadShortcuts();
        }
        return res;
    }

    return tab->save();
}

bool MainWindow::execSaveAs(TuningTab *tab) {
    QString filename = tab->fullFileName();
    QString path = QFileDialog::getSaveFileName(this, tr("Save As"), filename, saveFilterString);
    if (path.isEmpty()) {
        return false;
    }

    // Attempt to cover an opening file
    int existIndex = findTuningTab(path);
    if (existIndex >= 0 && existIndex != tabs->currentIndex()) {
        QMessageBox::warning(this, MainTitle,
                             tr("You can't overwrite a file opened in QSynthesis!"));
        return false;
    }

    // Save the file
    bool aResult = tab->saveAs(path);
    if (aResult) {
        settingIni.projects.advance(tab->filename());
        // saveSettingIni();
        reloadRecentMenu();
    }

    return aResult;
}

bool MainWindow::execImport() {
    QString path = QFileDialog::getOpenFileName(this, tr("Import"), ".", importFilterString);
    if (!path.isEmpty()) {
        QString suffix = PathFindSuffix(path).toLower();
        if (suffix == "mid") {
            SectionNotes notes;
            bool success = parseMidiFile(path, notes);
            if (!success) {
                return false;
            }
            addEmptyTab(notes);
        }
        return true;
    } else {
        return false;
    }
}
