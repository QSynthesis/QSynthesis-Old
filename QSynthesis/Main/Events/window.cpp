#include "mainwindow.h"

void MainWindow::resizeEvent(QResizeEvent *event) {
    updatePreviewer();
}

void MainWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::ActivationChange) {
        if (this->isActiveWindow()) {
            // Occurs when window is activated
            CentralTab *tab = currentTab();
            if (tab) {
                tab->awake();
            }
        } else {
            CentralTab *tab = currentTab();
            if (tab) {
                tab->sleep();
            }
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    for (int i = tabs->count() - 1; i >= 0; --i) {
        if (!handleTabCloseRequent(i)) {
            event->ignore();
            return;
        }
    }
    event->accept();
}
