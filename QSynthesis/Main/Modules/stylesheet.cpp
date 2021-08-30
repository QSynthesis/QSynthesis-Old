#include "mainwindow.h"

void MainWindow::initStyleSheet() {
    QFile qss(":/themes/theme.qss");

    if (!qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "[I/O]"
                 << "Failed to load default stylesheet data.";
    }

    QString style = qss.readAll();
    qss.close();

    setStyleSheet(style);
}
