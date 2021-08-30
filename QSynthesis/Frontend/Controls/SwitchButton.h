#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>

#include "QUtils.h"

class SwitchButton : public QPushButton {
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = nullptr);
    explicit SwitchButton(QString text, QWidget *parent = nullptr);

    int textWidth() const;
    int textHeight() const;

    void setRecommendedSize(double w, double h);

private:
    void init();
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void doubleClicked();
};

class SwitchButtonGroup : public QObject {
    Q_OBJECT
public:
    SwitchButtonGroup(QObject *parent);

    void addButton(SwitchButton *btn);
    void removeButton(SwitchButton *btn);

    int currentIndex();
    void setCurrentIndex(int index);

    SwitchButton *currentButton();

private:
    void updateSelected(bool checked);
    void onOneDoubleClicked();

    SwitchButton *m_current;
    QList<SwitchButton *> btns;

signals:
    void switched();
    void oneDoubleClicked();
};

#endif // SWITCHBUTTON_H
