#include "mainwindow.h"

void MainWindow::initStyleSheet() {
    QFile qss;
    qss.setFileName(":/themes/mainwindow.qss");
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
}
