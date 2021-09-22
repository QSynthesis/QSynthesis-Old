#ifndef KEYMODIFYDIALOG_H
#define KEYMODIFYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "Controls/FixedLineEdit.h"

// Widget to get the key modified.
class KeyModifyDialog : public QDialog {
    Q_OBJECT

public:
    explicit KeyModifyDialog(QWidget *parent = nullptr);
    ~KeyModifyDialog();

    QString text() const;

    int key() const;
    int modifiers() const;

private:
    QVBoxLayout *mainLayout;
    QLabel *hintLable;
    FixedLineEdit *lineEdit;

    Qt::Key m_tempKey;
    int m_keyBind;
    int m_modifiers;

    void setText(const QString &text);

private:
    bool keyDownEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void enter(QString text);

private:
    void handleEntered();
};

#endif // KEYMODIFYDIALOG_H
