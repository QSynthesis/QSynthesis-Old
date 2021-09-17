#include "Singletons/ColorTheme.h"
#include "mainwindow.h"

void MainWindow::initStyleSheet() {
    ColorTheme::loadTheme(qSetting->themeIndex);
}
