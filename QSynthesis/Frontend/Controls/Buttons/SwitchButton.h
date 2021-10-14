#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>

#include "QUtils.h"
#include "SwitchButtons/SwitchButtonGroup.h"
#include "SwitchButtons/SwitchButtonUnderline.h"

class SwitchButton : public QPushButton {
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = nullptr);
    explicit SwitchButton(QString text,QWidget *parent = nullptr);

    int textWidth() const;
    int textHeight() const;

    void setRecommendedSize(double w, double h);

private:
    void init();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void doubleClicked();
};

#endif // SWITCHBUTTON_H
