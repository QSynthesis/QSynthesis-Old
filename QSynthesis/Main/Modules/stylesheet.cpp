#include "mainwindow.h"

void MainWindow::initStyleSheet() {
    QFile qss;
#ifdef __APPLE__
    qss.setFileName(":/themes/theme-mac.qss");
#else
    qss.setFileName(":/themes/theme-win-dark.qss");
#endif
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
}
