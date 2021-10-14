#ifndef TEXTBOXTAB_H
#define TEXTBOXTAB_H

#include <QString>
#include <QVBoxLayout>

#include "Widgets/BaseTab.h"
#include "Controls/Inputs/FixedTextEdit.h"

class TextBoxTab : public BaseTab {
    Q_OBJECT
public:
    explicit TextBoxTab(TabWidget *parent = nullptr);

    void setText(const QString &text);
    QString text() const;

    void setReadOnly(bool readonly);
    bool readonly() const;

private:
    FixedTextEdit *textBox;
    QVBoxLayout *mainLayout;

    void init();

    void handleTextChanged();

signals:
    void textChanged(QString text);
};

#endif // TEXTBOXTAB_H
