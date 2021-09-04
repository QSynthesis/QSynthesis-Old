#include "BaseDialog.h"
#include "mainwindow.h"

#include <QCloseEvent>
BaseDialog::BaseDialog(QWidget *parent) {
    setWindowFlags(Qt::WindowCloseButtonHint);
}

BaseDialog::~BaseDialog() {
}

void BaseDialog::closeEvent(QCloseEvent *event) {
    event->accept();
}
