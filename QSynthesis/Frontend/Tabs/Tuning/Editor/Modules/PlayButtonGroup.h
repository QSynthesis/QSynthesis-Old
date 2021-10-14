#ifndef PLAYBUTTONGROUP_H
#define PLAYBUTTONGROUP_H

#include <QWidget>

#include "Controls/Buttons/VectorButton.h"

class PlayButtonGroup : public QWidget {
    Q_OBJECT
public:
    explicit PlayButtonGroup(QWidget *parent = nullptr);

    VectorButton *btnPlay, *btnStop, *btnStart, *btnEnd;

private:
    QHBoxLayout *mainLayout;

private:
    void onPlayBtnClicked();
    void onStopBtnClicked();
    void onStartBtnClicked();
    void onEndBtnClicked();

signals:
    void play();
    void stop();
    void start();
    void end();
};

#endif // PLAYBUTTONGROUP_H
