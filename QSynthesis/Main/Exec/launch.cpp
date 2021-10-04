#include "Utils/Templates.h"
#include "mainwindow.h"

void MainWindow::fromCommandLine() {
    QStringList args = QApplication::arguments();
    QStringList paths;

    if (args.size() < 2) {
        addWelcomeTab(); // If argument is only the exe path, add a welcoming tab
    } else {
        addMultipleTabs(args);
    }
}

void MainWindow::fromApplication() {
    addWelcomeTab();
    reloadTitle(); // Initialize Window Title
}
