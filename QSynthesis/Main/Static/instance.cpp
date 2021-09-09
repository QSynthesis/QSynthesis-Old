#include "mainwindow.h"

MainWindow *MainWindow::self = nullptr;

MainWindow *MainWindow::instance() {
    return self;
}
