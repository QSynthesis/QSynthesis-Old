#ifndef TEXTCONTROL_H
#define TEXTCONTROL_H

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QSlider>
#include <QWidget>

#include "../Inputs/FixedTextEdit.h"
#include "QUtils.h"

class TextControl : public QWidget {
    Q_OBJECT
public:
    explicit TextControl(QWidget *parent = NULL);
    explicit TextControl(QString text,QWidget *parent = NULL);
    explicit TextControl(QString text, QString value,QWidget *parent = NULL);

    void setCaption(QString caption);

    QString caption() const;

    void setMargin(int n);

    void setValue(QString value);
    QString getValue() const;

    QPlainTextEdit *Text() const;

    void moveCursorToEnd();

private:
    QString value;

    void InitTextControl(QString text, QString value);
    void onModifyAction();
    void onTextChanged(QString s);

    FixedTextEdit *pText;
    QLabel *pLabel;
    QVBoxLayout *pLayout;
};

#endif // TEXTCONTROL_H
