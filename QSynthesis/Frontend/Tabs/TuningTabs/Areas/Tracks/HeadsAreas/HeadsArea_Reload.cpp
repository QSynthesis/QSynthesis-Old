#include "../../../Modules/Elements/TrackHead.h"
#include "../../../TuningGroup.h"
#include "../HeadsArea.h"

void HeadsArea::reloadByVoice(const QString &voice) {
    for (auto it = Tracks.begin(); it != Tracks.end(); ++it) {
        TrackHead *head = *it;
        if (head->voiceDir() == voice) {
            head->updateStatus();
        }
    }
}
