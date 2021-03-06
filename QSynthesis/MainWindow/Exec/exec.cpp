#include "QSTabs.h"
#include "SettingIniFile.h"
#include "Utils/FileParser.h"
#include "application.h"
#include "mainwindow.h"

bool MainWindow::execOpen() {
    QStringList paths =
        QFileDialog::getOpenFileNames(nullptr, tr("Open File"), ".", openFilterString);
    if (!paths.isEmpty()) {
        return addMultipleTabs(paths);
    } else {
        return false;
    }
}

bool MainWindow::execOpenFolder() {
    QString path = QFileDialog::getExistingDirectory(nullptr, tr("Open Voice Bank"));
    if (!path.isEmpty()) {
        // path = removeTailSlashes(path);
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
            *qShortcuts = tab1->keys;
            reloadShortcuts();
        }
        return res;
    }

    return tab->save();
}

bool MainWindow::execSaveAs(TuningTab *tab) {
    QString filename = tab->fullFileName();
    QString path =
        QFileDialog::getSaveFileName(nullptr, tr("Save As"), filename, saveFilterString, nullptr);
    if (path.isEmpty()) {
        return false;
    }

    // Check Twice
    if (!path.endsWith(".ust", Qt::CaseInsensitive)) {
        path.append(".ust");
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
        qSetting->projects.advance(tab->filename());
        // saveSettingIni();
        reloadRecentMenu();
    }

    return aResult;
}

bool MainWindow::execImport() {
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Import"), ".", importFilterString);
    if (!path.isEmpty()) {
        FileParser parser(this);
        SectionNotes notes;
        if (parser.parseFile(path, notes)) {
            addEmptyTab(notes);
            return true;
        }
    }
    return false;
}
