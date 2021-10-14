#include "application.h"
#include "mainwindow.h"

void MainWindow::initMemory() {
    if (!qMemory->load()) {
        qApp->exitOnPermissionDenied();
    }
}
