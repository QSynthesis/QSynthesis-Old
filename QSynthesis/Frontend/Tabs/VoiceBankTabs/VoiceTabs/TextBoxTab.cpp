#include "TextBoxTab.h"

TextBoxTab::TextBoxTab(TabWidget *parent) : BaseTab(parent) {
    init();
}

void TextBoxTab::setText(const QString &text) {
    textBox->blockSignals(true);
    textBox->setText(text);
    textBox->blockSignals(false);
}

QString TextBoxTab::text() const {
    return textBox->text();
}

void TextBoxTab::setReadOnly(bool readonly) {
    textBox->setReadOnly(readonly);
}

bool TextBoxTab::readonly() const {
    return textBox->isReadOnly();
}

void TextBoxTab::init() {
    textBox = new FixedTextEdit();

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(textBox);
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    connect(textBox, &FixedTextEdit::editingFinished2, this, &TextBoxTab::handleTextChanged);
}

void TextBoxTab::handleTextChanged() {
    emit textChanged(textBox->text());
}
