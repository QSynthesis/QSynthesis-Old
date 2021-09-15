#include "mainwindow.h"

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
}

void MainWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::ActivationChange) {
        if (this->isActiveWindow()) {
            // Occurs when window is activated
            CentralTab *tab = currentTab();
            if (tab) {
                tab->awake();
            }
        } else {
            CentralTab *tab = currentTab();
            if (tab) {
                tab->sleep();
            }
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    for (int i = tabs->count() - 1; i >= 0; --i) {
        if (!handleTabCloseRequent(i)) {
            event->ignore();
            return;
        }
    }
    event->accept();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::handleGraphicsSceneEvents(QGraphicsSceneEvent *event) {
    QList<QEvent::Type> types{QEvent::GraphicsSceneDragEnter, QEvent::GraphicsSceneDragMove,
                              QEvent::GraphicsSceneDragLeave, QEvent::GraphicsSceneDrop};
    if (types.indexOf(event->type()) >= 0) {
        QGraphicsSceneDragDropEvent *dragDropEvent =
            static_cast<QGraphicsSceneDragDropEvent *>(event);

        switch (dragDropEvent->type()) {
        case QEvent::GraphicsSceneDragEnter: {
            QDragEnterEvent e(dragDropEvent->pos().toPoint(), dragDropEvent->possibleActions(),
                              dragDropEvent->mimeData(), dragDropEvent->buttons(),
                              dragDropEvent->modifiers());
            dragEnterEvent(&e);
            break;
        }
        case QEvent::GraphicsSceneDragMove: {
            QDragMoveEvent e(dragDropEvent->pos().toPoint(), dragDropEvent->possibleActions(),
                             dragDropEvent->mimeData(), dragDropEvent->buttons(),
                             dragDropEvent->modifiers());
            dragMoveEvent(&e);
            break;
        }
        case QEvent::GraphicsSceneDragLeave: {
            QDragLeaveEvent e;
            dragLeaveEvent(&e);
            break;
        }
        case QEvent::GraphicsSceneDrop: {
            QDropEvent e(dragDropEvent->pos().toPoint(), dragDropEvent->possibleActions(),
                         dragDropEvent->mimeData(), dragDropEvent->buttons(),
                         dragDropEvent->modifiers());
            dropEvent(&e);
            break;
        }
        default:
            break;
        }
    }
}
