#include "mainwindow.h"

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
}

void MainWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::ActivationChange) {
        if (this->isActiveWindow()) {
            // Occurs when window is activated
            CentralTab *tab = currentTab();
            if (tab) {
                tab->awake();
            }
            emit awake();
        } else {
            CentralTab *tab = currentTab();
            if (tab) {
                tab->sleep();
            }
            emit sleep();
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
