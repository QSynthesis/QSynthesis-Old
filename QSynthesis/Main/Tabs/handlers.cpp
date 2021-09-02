#include "mainwindow.h"

bool MainWindow::handleTabCloseRequent(int index) {
    CentralTab *tab = tabAt(index);

    bool accept = true;
    QString title;

    switch (tab->tabType()) {
    case Qs::Tuning: {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        accept = !(tab1->isDeleted() || tab1->isEdited());
        title = tr("You have not saved the file, do you want to save it?");
    } break;
    case Qs::Folder:
        accept = !(tab->isEdited());
        title = tr("You have not saved the directory, do you want to save it?");
        break;
    case Qs::Setting:
    case Qs::Keyboard:
        accept = !(tab->isEdited());
        title = tr("You have not saved the configuration, do you want to save it?");
        break;
    default:
        break;
    }

    if (!accept) {
        QMessageBox::StandardButton result = QMessageBox::question(
            this, MainTitle, title, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
            QMessageBox::Yes);
        switch (result) {
        case QMessageBox::Yes:
            accept = execSave(tab);
            break;
        case QMessageBox::No:
            accept = true;
            break;
        default:
            accept = false;
            break;
        }
    }

    if (accept) {
        removeTab(index);
        return true;
    }

    return false;
}

void MainWindow::handleTabIndexChanged(int index) {
    CentralTab *tab = currentTab();
    if (!tab) {
        return;
    }
    setCurrentActions(tab->tabType());
    tab->awake();

    reloadTitle(); // Reload Window Title refering to current tab
}

void MainWindow::handleTabNameChanged(int index, const QString &newName) {
    reloadTitle();
}
