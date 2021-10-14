#include "FixedComboBox.h"

FixedComboBox::FixedComboBox(QWidget *parent) : QComboBox(parent) {
    setEditable(true);
}

FixedComboBox::~FixedComboBox() {
}
