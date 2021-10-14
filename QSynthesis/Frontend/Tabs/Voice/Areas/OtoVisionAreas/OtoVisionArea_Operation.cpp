#include "../../Operations/OtoOperations/OtoChangeOperation.h"
#include "../../VoiceBankGroup.h"
#include "../OtoVisionArea.h"

void OtoVisionArea::saveOperation(OtoOperation *o) {
    o = static_cast<OtoOperation *>(o->simplify(o));
    if (o) {
        m_ptrs->tab->addHistory(o);
    } else {
        qDebug() << "[NonOtoOperation]"
                 << "Addition Refused";
    }
}
