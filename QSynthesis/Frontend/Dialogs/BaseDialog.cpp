#include "BaseDialog.h"

#include <QCloseEvent>

BaseDialog::BaseDialog(QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint) {
    setFocusPolicy(Qt::ClickFocus);
}

BaseDialog::~BaseDialog() {
}

void BaseDialog::closeEvent(QCloseEvent *event) {
    event->accept();
}
