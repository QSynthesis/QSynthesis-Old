#include "Utils/Templates.h"
#include "mainwindow.h"

void MainWindow::fromCommandLine(const QStringList &args) {
    QStringList paths;

    if (tabs->count() == 0 && args.size() < 2) {
        addWelcomeTab(); // If argument is only the exe path, add a welcoming tab
    } else {
        addMultipleTabs(args.mid(1));
    }

    raise();
}

void MainWindow::fromApplication() {
    addWelcomeTab();
    reloadTitle(); // Initialize Window Title
}
