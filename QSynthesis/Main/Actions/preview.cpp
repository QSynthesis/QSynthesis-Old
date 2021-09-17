#include "Singletons/ColorTheme.h"
#include "mainwindow.h"

void MainWindow::handleOpenThemes() {
    QStringList list = {"Light (Default)", "Dark (Default)"};
    int index = tabs->useSelector(list, tr("Select color theme (Up/down keys to preview)"),
                                  qSetting->themeIndex, ColorTheme::loadTheme);

    if (index < 0) {
        ColorTheme::loadTheme(qSetting->themeIndex);
    } else {
        qSetting->themeIndex = index;
    }
}

void MainWindow::handleOpenLanguages() {
}
