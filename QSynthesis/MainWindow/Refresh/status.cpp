#include "mainwindow.h"

void MainWindow::reloadTitle() {
    QString title = tabs->currentTitle() + " - " + WindowTitle;
    this->setWindowTitle(title);
}
