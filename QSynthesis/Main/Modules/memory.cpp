#include "Managers/MemoryManager.h"
#include "mainwindow.h"

void MainWindow::initMemory() {
    if (!qMemory->load()) {
        exitOnNoIOPermission();
    }
}
