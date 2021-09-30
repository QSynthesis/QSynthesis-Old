#include "mainwindow.h"

void MainWindow::exitOnNoIOPermission() {
    QMessageBox::critical(nullptr, ErrorTitle, tr("No write file permission!"));
    exit(1);
}
