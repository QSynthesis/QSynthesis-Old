#ifndef OTOPLAYERAREA_H
#define OTOPLAYERAREA_H

#include "../Modules/PlayerLabel.h"
#include "QUtauBasic.h"
#include "VoiceBankArea.h"

#include <QLabel>
#include <QVBoxLayout>

class OtoPlayerArea : public VoiceBankArea {
    Q_OBJECT
public:
    explicit OtoPlayerArea(VoiceBankTab *tab, QWidget *parent = nullptr);
    ~OtoPlayerArea();

private:
    void init();

public:
    void initExtern();

public:
    void setMedia(const QGenonSettings &sample, double duration, int rate, int depth, int channels);
    void removeMedia();

    void updateCaption();

    void advancePlaying(qint64 position);
    void setPlaying(bool playing);

    void receiveFromVision(const QGenonSettings &sample);

private:
    QVBoxLayout *mainLayout;
    QLabel *lbCaption;
    PlayerLabel *controller;

    QGenonSettings m_sample;

    double m_duration;
    int m_rate;
    int m_depth;
    int m_channels;

    void handlePlayerPlayed(bool play);
    void handlePlayerJumped(double percent);

signals:
};

#endif // OTOPLAYERAREA_H
