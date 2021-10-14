#ifndef PLAYERLABEL_H
#define PLAYERLABEL_H

#include <QGridLayout>
#include <QSlider>

#include "Controls/Buttons/VectorButton.h"

class PlayerLabel : public QWidget {
    Q_OBJECT
public:
    explicit PlayerLabel(QWidget *parent = nullptr);
    ~PlayerLabel();

public:
    double percentA() const;
    void setPercentA(double percentA);

    double percentB() const;
    void setPercentB(double percentB);

    void clearPercent();

    void advancePlaying(double percent);

    bool abOnly() const;
    bool pressed() const;

public:
    void setPlaying(bool playing);
    void setABOnly(bool value);

private:
    QGridLayout *mainLayout;
    QSlider *slider;

    VectorButton *btnPlay, *btnABPlay;

    double m_percentA;
    double m_percentB;

    bool m_abOnly;
    bool m_pressed;

private:
    void handleSliderPressed();
    void handleSliderMoved(int position);
    void handleSliderReleased();

    void handlePlayBtnClicked();
    void handleABPlayBtnClicked();

signals:
    void played(bool play = false);
    void jumped(double percent);
};

#endif // PLAYERLABEL_H
