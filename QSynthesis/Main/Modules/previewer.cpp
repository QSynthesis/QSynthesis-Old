#include "mainwindow.h"

void MainWindow::initPreviewer() {
    previewer = new TopComboBox(tabs);
    // previewer->setCurrentText("shichenhaoshitiancai");
    // previewer->addItems({"Dark(Default)", "Light(Default)", "UTAU", "Synthesizer V"});
    previewer->hide();
}

void MainWindow::updatePreviewer() {
    if (previewer->isVisible()) {
        previewer->adjustSize();
        previewer->resize(centralWidget()->width() / 2, previewer->height());
        previewer->move((centralWidget()->width() - previewer->width()) / 2, 0);
    }
}

void MainWindow::showPreviewer() {
    previewer->show();
    updatePreviewer();
}
