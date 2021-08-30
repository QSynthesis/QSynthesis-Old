#include "../../Operations/OtoOperations/OtoChangeOperation.h"
#include "../../Operations/OtoOperations/OtoMoveOperation.h"
#include "../../Operations/OtoOperations/OtoVariateOperation.h"
#include "../../VoiceBankGroup.h"
#include "../OtoDataArea.h"

void OtoDataArea::saveOperation(OtoOperation *o) {
    if (o->differ()) {
        m_ptrs->tab->addHistory(o);
    } else {
        qDebug() << "[NonOtoOperation]"
                 << "Addition Refused";
        delete o;
    }
}

bool OtoDataArea::handleOperation(OtoOperation *o, bool undo) {
    OtoOperation::Type type = o->type();

    auto it = TableMap.find(o->dirname());
    if (it == TableMap.end()) {
        return false;
    }

    OtoTableTab *tab = it.value();
    otoTabs->setCurrentWidget(tab);

    switch (type) {
    case OtoOperation::Change: {
        OtoChangeOperation *oc = static_cast<OtoChangeOperation *>(o);
        const QGenonSettings &value = undo ? oc->origin() : oc->modified();
        tab->changeSample(value, oc->index());
        break;
    }
    case OtoOperation::Add:
    case OtoOperation::Remove: {
        OtoVariateOperation *ov = static_cast<OtoVariateOperation *>(o);
        int f = (type == OtoOperation::Add) ? 1 : -1;
        int f2 = undo ? -1 : 1;
        if (f * f2 > 0) {
            tab->addSample(ov->sample(), ov->index());
        } else {
            tab->removeSample(ov->sample(), ov->index());
        }
        break;
    }
    case OtoOperation::Move: {
        OtoMoveOperation *om = static_cast<OtoMoveOperation *>(o);
        int currentIndex = undo ? (om->index() + om->movement()) : (o->index());
        int currentMovement = undo ? (-om->movement()) : om->movement();
        tab->moveSample(om->sample(), currentIndex, currentMovement);
        break;
    }
    default:
        break;
    }
    return true;
}

void OtoDataArea::receiveFromVision(const QGenonSettings &sample) {
    auto it = TableMap.find(PathFindUpper(sample.mFileName));
    if (it == TableMap.end()) {
        return;
    }

    OtoTableTab *tab = it.value();
    if (otoTabs->currentWidget() != tab) {
        otoTabs->setCurrentWidget(tab);
    }
    tab->setCurrentSample(sample);
}

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
