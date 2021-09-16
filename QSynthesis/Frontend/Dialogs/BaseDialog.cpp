#include "BaseDialog.h"
#include "mainwindow.h"

#include <QCloseEvent>
BaseDialog::BaseDialog(QWidget *parent) {
    setWindowFlags(Qt::WindowCloseButtonHint);
    setFocusPolicy(Qt::ClickFocus);
}

BaseDialog::~BaseDialog() {
}

void BaseDialog::closeEvent(QCloseEvent *event) {
    event->accept();
}
