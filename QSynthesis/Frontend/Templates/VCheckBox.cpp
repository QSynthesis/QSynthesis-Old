#include "VCheckBox.h"
#include "Methods.h"

#include <QStyleOptionButton>
#include <QStylePainter>

VCheckBox::VCheckBox(QWidget *parent) : QAbstractButton(parent) {
}

VCheckBox::VCheckBox(QString text, QWidget *parent) : QAbstractButton(parent) {
    setText(text);
}

void VCheckBox::paintEvent(QPaintEvent *) {
}
