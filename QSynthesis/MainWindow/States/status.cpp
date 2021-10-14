#include "mainwindow.h"

void MainWindow::reloadTitle() {
    QString title = tabs->currentTitle() + " - " + WindowTitle;
    setWindowTitle(title);
}
