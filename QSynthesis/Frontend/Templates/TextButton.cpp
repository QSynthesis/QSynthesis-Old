#include "TextButton.h"

TextButton::TextButton(QWidget *parent) : QPushButton(parent) {
}

TextButton::TextButton(const QString &text, QWidget *parent) : QPushButton(text, parent) {
}

TextButton::~TextButton() {
}
