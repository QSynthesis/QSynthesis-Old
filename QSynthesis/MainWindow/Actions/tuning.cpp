#include "Tabs/Tuning/TuningTab.h"
#include "Utils/FileParser.h"
#include "mainwindow.h"

void MainWindow::handleAppendFile() {
    CentralTab *tab = currentTab();
    TuningTab *tab1;
    if (tab->tabType() == Qs::Tuning) {
        tab1 = qobject_cast<TuningTab *>(tab);
    } else {
        return;
    }

    QString path = QFileDialog::getOpenFileName(nullptr, tr("Append"), ".", appendFilterString);
    if (!path.isEmpty()) {
        FileParser parser(this);
        SectionNotes notes;
        if (parser.parseFile(path, notes)) {
            tab1->appendFile(notes);
        }
    }
}

void MainWindow::handleExportSelection() {
    QString path = QFileDialog::getSaveFileName(nullptr, tr("Export selection"), ".",
                                                exportSelectionFilterString);
    if (!path.isEmpty()) {
    } else {
    }
}

void MainWindow::handleExportTrack() {
    QString path =
        QFileDialog::getSaveFileName(this, tr("Export entire track"), ".", exportTrackFilterString);
    if (!path.isEmpty()) {
    } else {
    }
}

void MainWindow::handleCopyNotes() {
    qDebug() << "[Action]"
             << "Copy";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->copy();
    }
}

void MainWindow::handleCutNotes() {
    qDebug() << "[Action]"
             << "Cut";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->cut();
    }
}

void MainWindow::handlePasteNotes() {
    qDebug() << "[Action]"
             << "Paste";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->paste();
    }
}

void MainWindow::handleRemoveNotes() {
    qDebug() << "[Action]"
             << "Remove Notes";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->remove();
    }
}

void MainWindow::handleInsertLyrics() {
    qDebug() << "[Action]"
             << "Insert Lyrics";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->showLyricInsertion();
    }
}

void MainWindow::handleFindReplace() {
    qDebug() << "[Action]"
             << "Find And Replace";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->showFindReplace();
    }
}

void MainWindow::handleTranspose() {
    qDebug() << "[Action]"
             << "Transpose";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->transpose();
    }
}

void MainWindow::handleOctaveUp() {
    qDebug() << "[Action]"
             << "Transpose";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->transpose(12);
    }
}

void MainWindow::handleOctaveDown() {
    qDebug() << "[Action]"
             << "Transpose";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->transpose(-12);
    }
}

void MainWindow::handleRemoveRest() {
    qDebug() << "[Action]"
             << "Remove rest";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->removeRest();
    }
}

void MainWindow::handleInsertRest() {
    qDebug() << "[Action]"
             << "Insert rest";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->insertRest();
    }
}

void MainWindow::handleP2P3Fade() {
    qDebug() << "[Action]"
             << "P2 P3";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setP2P3Fade();
    }
}

void MainWindow::handleP1P4Fade() {
    qDebug() << "[Action]"
             << "P1 P4";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setP1P4Fade();
    }
}

void MainWindow::handleResetEnvelope() {
    qDebug() << "[Action]"
             << "Reset Envelope";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->resetEnvelope();
    }
}

void MainWindow::handleNoteProperty() {
    qDebug() << "[Action]"
             << "Note Property";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->showNoteProperty();
    }
}

void MainWindow::handleMoveToStart() {
    qDebug() << "[Action]"
             << "Move to start";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->moveToStart();
    }
}

void MainWindow::handleMoveToEnd() {
    qDebug() << "[Action]"
             << "Move to end";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->moveToEnd();
    }
}

void MainWindow::handleRemoveCache() {
    qDebug() << "[Action]"
             << "Remove cahce";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->removeAllCaches();
    }
}

void MainWindow::handleExportAudio() {
    qDebug() << "[Action]"
             << "Export Audio";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->exportRecentAudio();
    }
}

void MainWindow::handleLyricConfig() {
    qDebug() << "[Action]"
             << "Lyric Configue";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->configueLyric();
    }
}

void MainWindow::handlePrefixConfig() {
    qDebug() << "[Action]"
             << "Prefix Map";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->configuePrefix();
    }
}
