#include "mainwindow.h"

void MainWindow::reloadTitle() {
    QString title = tabs->currentTitle() + " - " + MainTitle;
    this->setWindowTitle(title);
}
