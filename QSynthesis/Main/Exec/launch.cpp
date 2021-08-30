#include "mainwindow.h"

void MainWindow::fromCommandLine(int argc, char **argv) {
    if (argc < 2) {
        addWelcomeTab(); // If argument is only the exe path, add a welcoming tab
    } else {
        QStringList paths;
        for (int i = 1; i < argc; ++i) {
            paths.append(QString::fromLocal8Bit(argv[i])); // Add tabs one by one
        }

        if (paths.size() == 1) {
            addTuningTab(paths[0]);
        } else {
            addMultipleTabs(paths);
        }
    }

    reloadTitle(); // Initialize Window Title
}

void MainWindow::fromApplication() {
    addWelcomeTab();
    reloadTitle(); // Initialize Window Title
}
