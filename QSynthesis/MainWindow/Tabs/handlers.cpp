#include "QSTabs.h"
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
        tabs->setCurrentIndex(index);

        QMessageBox msgbox(this);
        msgbox.setText(title);
        msgbox.setWindowTitle(MainTitle);
        msgbox.setIcon(QMessageBox::Question);
        msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgbox.setDefaultButton(QMessageBox::Yes);

        msgbox.button(QMessageBox::Yes)->setText(tr("Save(&S)"));
        msgbox.button(QMessageBox::No)->setText(tr("Don't save(&N)"));
        msgbox.button(QMessageBox::Cancel)->setText(tr("Cancel"));

        QMessageBox::StandardButton result =
            static_cast<QMessageBox::StandardButton>(msgbox.exec());

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
    reloadTitle(); // Reload Window Title refering to current tab

    welcomeActions->switchFile->setEnabled(previousTab());
}

void MainWindow::handleTabNameChanged(int index, const QString &newName) {
    reloadTitle();
}

void MainWindow::handleTabPressed(int index, Qt::MouseButton button) {
    if (button == Qt::RightButton) {
        CentralTab *tab = tabAt(index);
        if (!tab) {
            return;
        }
        QStringList list{tr("Close"), tr("Close Others"), tr("Close Saved"), tr("Close All")};

        if (tab->tabType() == Qs::Tuning) {
            QString revealStr;
            revealStr = tr("Show in %1(&S)").arg(fileManagerName);
            list << "" << revealStr;
        } else if (tab->tabType() == Qs::Folder) {
            QString revealStr;
            revealStr = tr("Open in %1(&S)").arg(fileManagerName);
            list << "" << revealStr;
        }

        TemporaryMenu *menu = new TemporaryMenu(list, this);
        int action = menu->start();
        menu->deleteLater();

        switch (action) {
        case 0:
            handleTabCloseRequent(index);
            break;
        case 1:
            for (int i = tabs->count() - 1; i >= 0; --i) {
                if (i == index) {
                    continue;
                }
                if (!handleTabCloseRequent(i)) {
                    break;
                }
            }
            break;
        case 2:
            for (int i = tabs->count() - 1; i >= 0; --i) {
                if (tabAt(i)->isEdited()) {
                    continue;
                }
                if (!handleTabCloseRequent(i)) {
                    break;
                }
            }
            break;
        case 3:
            for (int i = tabs->count() - 1; i >= 0; --i) {
                if (!handleTabCloseRequent(i)) {
                    break;
                }
            }
            break;
        case 4:
            RevealFile(tabAt(index)->filename());
            break;
        default:
            break;
        }
    }
}
