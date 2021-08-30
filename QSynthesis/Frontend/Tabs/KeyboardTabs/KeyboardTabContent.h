#ifndef KEYBOARDTABCONTENT_H
#define KEYBOARDTABCONTENT_H

#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "../CentralTab.h"
#include "KeyLabelContent.h"
#include "KeyTableWidget.h"

class KeyboardTab;

// Main Content of Keyboard Mapping Tab Class.
class KeyboardTabContent : public QWidget {
    Q_OBJECT
public:
    explicit KeyboardTabContent(KeyboardTab *tab, QWidget *parent = nullptr);

    KeyTableWidget *tableWidget;

private:
    KeyboardTab *m_tab;

    QVBoxLayout *mainLayout;
    QLineEdit *filterEdit;

private:
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);

public slots:
    void filterRows(const QString &text);
};

#endif // KEYBOARDTABCONTENT_H
