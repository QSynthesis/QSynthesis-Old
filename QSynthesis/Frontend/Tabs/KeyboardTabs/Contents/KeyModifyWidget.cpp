#include "KeyModifyWidget.h"

KeyModifyWidget::KeyModifyWidget(QWidget *parent) : QDialog(parent) {
    //自动关闭
    setWindowFlags(Qt::Popup);

    setFixedSize(500, 100);
    mainLayout = new QVBoxLayout();
    hintLable = new QLabel(tr("Press desired key combination and then press ENTER."));
    lineEdit = new KeyLineEdit();

    //居中
    QPoint globalPos = parent->mapToGlobal(QPoint(0, 0));      //父窗口绝对坐标
    int x = globalPos.x() + (parent->width() - width()) / 2;   // x坐标
    int y = globalPos.y() + (parent->height() - height()) / 2; // y坐标
    move(x, y);                                                //窗口移动

    mainLayout->addWidget(hintLable);
    mainLayout->addWidget(lineEdit);
    setLayout(mainLayout);

    lineEdit->setFocus();

    //信号
    connect(lineEdit, &KeyLineEdit::enterModify, this, &KeyModifyWidget::handleEntered);
}

QString KeyModifyWidget::text() const {
    return lineEdit->text();
}

void KeyModifyWidget::setText(const QString &text) {
    lineEdit->setText(text);
}

void KeyModifyWidget::handleEntered() {
    accept();
}
