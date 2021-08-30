#ifndef VOICEBANKGROUP_H
#define VOICEBANKGROUP_H

#include <QObject>

#include "../VoiceBankTab.h"

class VoiceBankGroup : public QObject {
    Q_OBJECT
public:
    explicit VoiceBankGroup(VoiceBankTab *parent = nullptr);
    friend QDebug operator<<(QDebug debug, const VoiceBankGroup &vg);

public:
    VoiceBankTab *tab;

    OtoInfoArea *infoArea;
    OtoDataArea *dataArea;
    OtoVisionArea *visionArea;

    WaveformArea *otoVision;
};

#endif // VOICEBANKGROUP_H
