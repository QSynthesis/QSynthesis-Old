#include "../../Operations/OtoOperations/OtoChangeOperation.h"
#include "../../VoiceBankGroup.h"
#include "../OtoVisionArea.h"

void OtoVisionArea::saveOperation(OtoOperation *o) {
    if (o->differ()) {
        m_ptrs->tab->addHistory(o);
    } else {
        qDebug() << "[NonOtoOperation]"
                 << "Addition Refused";
        delete o;
    }
}
