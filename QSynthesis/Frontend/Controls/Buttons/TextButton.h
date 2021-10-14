#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <QPushButton>

class TextButton : public QPushButton {
    Q_OBJECT
public:
    explicit TextButton(QWidget *parent = nullptr);
    explicit TextButton(const QString &text,QWidget *parent = nullptr);
    ~TextButton();

signals:
};

#endif // TEXTBUTTON_H
