#include "VoiceBankTab.h"
#include "VoiceBankGroup.h"

bool VoiceBankTab::isFree() const {
    return isFreeButPlaying() && !isPlaying();
}

bool VoiceBankTab::isFreeButPlaying() const {
    return visionArea->editing();
}
