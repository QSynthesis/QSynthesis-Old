#include "QUtils.h"
#include "mainwindow.h"

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event) {
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event) {
}

void MainWindow::dropEvent(QDropEvent *event) {
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }
    QStringList fileNames;

    for (int i = 0; i < urls.size(); ++i) {
        fileNames.append(_FIN(urls[i].toLocalFile()));
    }

    addMultipleTabs(fileNames);
}
