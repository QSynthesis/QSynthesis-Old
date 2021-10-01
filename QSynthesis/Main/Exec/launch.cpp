#include "mainwindow.h"

void MainWindow::fromCommandLine() {
    QStringList args = QApplication::arguments();

    if (args.size() < 2) {
        addWelcomeTab(); // If argument is only the exe path, add a welcoming tab
    } else {
        QStringList paths;
        for (int i = 1; i < args.size(); ++i) {
            paths.append(args.at(i)); // Add tabs one by one
        }

        addMultipleTabs(paths);
    }
}

void MainWindow::fromApplication() {
    addWelcomeTab();
    reloadTitle(); // Initialize Window Title
}
