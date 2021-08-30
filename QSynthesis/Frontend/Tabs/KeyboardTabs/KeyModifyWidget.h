#ifndef KEYMODIFYWIDGET_H
#define KEYMODIFYWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "KeyLineEdit.h"

// Widget to get the key modified.
class KeyModifyWidget : public QDialog {
    Q_OBJECT
private:
    QVBoxLayout *mainLayout;
    QLabel *hintLable;
    KeyLineEdit *lineEdit;

public:
    explicit KeyModifyWidget(QWidget *parent = nullptr);

    QString text() const;
    void setText(const QString &text);

signals:
    void enter(QString text);

private:
    void handleEntered();
};

#endif // KEYMODIFYWIDGET_H
