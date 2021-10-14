#include "Tabs/Tuning/TuningTab.h"
#include "mainwindow.h"

QString MainWindow::incUntitled() {
    untitledCount++;
    return QString(UntitledFileName + " " + QString::number(untitledCount));
}

QString MainWindow::decUntitled() {
    untitledCount--;
    return QString(UntitledFileName + " " + QString::number(untitledCount));
}

void MainWindow::makeUntitled(TuningTab *tab, const QString &name) {
    QString title = name.isEmpty() ? incUntitled() : name;
    tab->setUntitled(true);
    tab->setFilename(title);
    tab->ustFile.sectionSettings().projectName = title;
}
