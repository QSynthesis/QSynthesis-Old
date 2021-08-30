#include "../../Operations/OtoOperations/OtoChangeOperation.h"
#include "../../VoiceBankGroup.h"
#include "../OtoVisionArea.h"

void OtoVisionArea::handleEditing() {
    m_editing = true;
    m_ptrs->dataArea->receiveFromVision(vision->sample());
}

void OtoVisionArea::handleEditOver(const QGenonSettings &orgSample) {
    m_editing = false;

    QGenonSettings origin = orgSample;
    QGenonSettings modified = vision->sample();
    int index = vision->index();

    OtoChangeOperation *oc = new OtoChangeOperation();
    oc->setDirname(PathFindUpper(origin.mFileName));
    oc->setIndex(index);
    oc->setOrigin(origin);
    oc->setModified(modified);

    saveOperation(oc);
}
