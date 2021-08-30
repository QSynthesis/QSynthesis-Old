#ifndef ENVBUTTONGROUP_H
#define ENVBUTTONGROUP_H

#include "VectorButton.h"

class EnvButtonGroup : public QWidget {
    Q_OBJECT
public:
    explicit EnvButtonGroup(QWidget *parent = nullptr);

    VectorButton *btnP2P3, *btnP1P4, *btnReset;

private:
    QHBoxLayout *mainLayout;

private:
    void onP2P3BtnClicked();
    void onP1P4BtnClicked();
    void onResetBtnClicked();

signals:
    void p2p3();
    void p1p4();
    void reset();
};
#endif // ENVBUTTONGROUP_H
