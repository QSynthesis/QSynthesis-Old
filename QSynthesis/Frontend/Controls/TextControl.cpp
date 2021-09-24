#include "TextControl.h"

TextControl::TextControl(QWidget *parent) : QWidget(parent) {
    InitTextControl("", "");
}

TextControl::TextControl(QString text, QWidget *parent) : QWidget(parent) {
    InitTextControl(text, "");
}

TextControl::TextControl(QString text, QString value, QWidget *parent) : QWidget(parent) {
    InitTextControl(text, value);
}

void TextControl::setCaption(QString caption) {
    pLabel->setText(caption);
    pLabel->adjustSize();
}

QString TextControl::caption() const {
    return pLabel->text();
}

void TextControl::setMargin(int n) {
    pLayout->setMargin(n);
}

void TextControl::setValue(QString value) {
    pText->setPlainText(value);
}

QString TextControl::getValue() const {
    return pText->toPlainText();
}

QPlainTextEdit *TextControl::Text() const {
    return pText;
}

void TextControl::moveCursorToEnd() {
    QTextDocument *doc = pText->document();
    QTextCursor cursor(doc);
    cursor.movePosition(QTextCursor::End);
    pText->setTextCursor(cursor);
}

void TextControl::InitTextControl(QString text, QString value) {
    pLabel = new QLabel(text, this);
    pText = new FixedTextEdit(value, this);

    pLabel->adjustSize();
    pText->adjustSize();

    pLayout = new QVBoxLayout(this);
    pLayout->setMargin(0);

    pLayout->addWidget(pLabel);
    pLayout->addWidget(pText, 1);

    setLayout(pLayout);
}
