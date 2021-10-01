#include "../../Operations/OtoOperations/OtoChangeOperation.h"
#include "../../Operations/OtoOperations/OtoMoveOperation.h"
#include "../../Operations/OtoOperations/OtoVariateOperation.h"
#include "../../VoiceBankGroup.h"
#include "../OtoDataArea.h"

void OtoDataArea::handleSampleChanged(const QGenonSettings &origin, const QGenonSettings &modified,
                                      int index) {
    OtoTableTab *tab = qobject_cast<OtoTableTab *>(sender());

    OtoChangeOperation *oc = new OtoChangeOperation();
    oc->setDirname(tab->dirname());
    oc->setIndex(index);
    oc->setOrigin(origin);
    oc->setModified(modified);

    saveOperation(oc);
}

void OtoDataArea::handleSampleMoved(const QGenonSettings &sample, int index, int movement) {
    OtoTableTab *tab = qobject_cast<OtoTableTab *>(sender());

    OtoMoveOperation *oc = new OtoMoveOperation();
    oc->setDirname(tab->dirname());
    oc->setIndex(index);
    oc->setSample(sample);
    oc->setMovement(movement);

    saveOperation(oc);
}

void OtoDataArea::handleSampleAdded(const QGenonSettings &sample, int index) {
    OtoTableTab *tab = qobject_cast<OtoTableTab *>(sender());

    OtoVariateOperation *oc = new OtoVariateOperation(true);
    oc->setDirname(tab->dirname());
    oc->setIndex(index);
    oc->setSample(sample);

    saveOperation(oc);
}

void OtoDataArea::handleSampleRemoved(const QGenonSettings &sample, int index) {
    OtoTableTab *tab = qobject_cast<OtoTableTab *>(sender());

    OtoVariateOperation *oc = new OtoVariateOperation(false);
    oc->setDirname(tab->dirname());
    oc->setIndex(index);
    oc->setSample(sample);

    saveOperation(oc);
}

void OtoDataArea::handleCurrentChanged(const QGenonSettings &genon, int index) {
    m_ptrs->visionArea->setSampleAndIndex(genon, index);
}

void OtoDataArea::handleSelectionChanged() {
    m_ptrs->tab->change();
}

void OtoDataArea::handleTabIndexChanged(int index) {
    OtoTableTab *prev = qobject_cast<OtoTableTab *>(otoTabs->previousTab());
    if (prev) {
        prev->selectNone();
    }
    m_ptrs->tab->change();
}
