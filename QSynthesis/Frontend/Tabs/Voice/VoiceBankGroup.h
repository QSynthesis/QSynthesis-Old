#ifndef VOICEBANKGROUP_H
#define VOICEBANKGROUP_H

#include "Central/LayerGroup.h"
#include "VoiceBankTab.h"

class VoiceBankGroup : public LayerGroup {
    Q_OBJECT
public:
    explicit VoiceBankGroup(VoiceBankTab *parent = nullptr);
    friend QDebug operator<<(QDebug debug, const VoiceBankGroup &vg);

public:
    VoiceBankTab *tab;

    OtoInfoArea *infoArea;
    OtoDataArea *dataArea;
    OtoVisionArea *visionArea;
    OtoPlayerArea *playerArea;

    WaveformArea *otoVision;
};

#endif // VOICEBANKGROUP_H
