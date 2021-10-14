#include "../../Operations/OtoOperations/OtoChangeOperation.h"
#include "../../Operations/OtoOperations/OtoMoveOperation.h"
#include "../../Operations/OtoOperations/OtoVariateOperation.h"
#include "../../VoiceBankGroup.h"
#include "../OtoDataArea.h"

void OtoDataArea::saveOperation(OtoOperation *o) {
    o = static_cast<OtoOperation *>(o->simplify(o));
    if (o) {
        m_ptrs->tab->addHistory(o);
    } else {
        qDebug() << "[NonOtoOperation]"
                 << "Addition Refused";
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
