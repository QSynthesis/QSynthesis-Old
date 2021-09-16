#ifndef LABELBUTTON_H
#define LABELBUTTON_H

#include <QPushButton>

class LabelButton : public QPushButton {
    Q_OBJECT
public:
    explicit LabelButton(QWidget *parent = nullptr);
    explicit LabelButton(const QString &text, QWidget *parent = nullptr);
    LabelButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    virtual ~LabelButton();

signals:
};

#endif // LABELBUTTON_H
