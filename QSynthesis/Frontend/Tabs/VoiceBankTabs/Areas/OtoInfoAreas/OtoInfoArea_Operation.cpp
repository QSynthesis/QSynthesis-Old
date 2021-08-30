#include "../../Operations/NonOtoOperations/InfoTextOperation.h"
#include "../../Operations/NonOtoOperations/PrefixOperation.h"
#include "../../VoiceBankGroup.h"
#include "../OtoInfoArea.h"

void OtoInfoArea::saveOperation(NonOtoOperation *no) {
    if (no->differ()) {
        m_ptrs->tab->addHistory(no);
    } else {
        qDebug() << "[NonOtoOperation]"
                 << "Addition Refused";
        delete no;
    }
}

bool OtoInfoArea::handleOperation(NonOtoOperation *no, bool undo) {
    switch (no->type()) {
    case NonOtoOperation::PrefixMap: {
        PrefixOperation *po = static_cast<PrefixOperation *>(no);
        int noteNum = po->noteNum();
        QString value = undo ? po->origin() : po->modified();
        if (po->prefixType() == Qs::Prefix) {
            m_prefixMap[noteNum] = value;
            prefixTab->setPrefix(noteNum, value);
        } else {
            m_suffixMap[noteNum] = value;
            prefixTab->setSuffix(noteNum, value);
        }
        break;
    }
    case NonOtoOperation::InfoText: {
        InfoTextOperation *io = static_cast<InfoTextOperation *>(no);
        QString value = undo ? io->origin() : io->modified();
        switch (io->property()) {
        case InfoTextOperation::Readme:
            setText(value);
            break;
        case InfoTextOperation::Name:
            setName(value);
            break;
        case InfoTextOperation::Author:
            setAuthor(value);
            break;
        case InfoTextOperation::Avatar:
            if (value.isEmpty()) {
                resetAvatar();
            } else if (!setAvatar(value)) {
                // QMessageBox::warning(nullptr, MainTitle, tr("This avatar file is
                // deleted.")); return false;
            }
            break;
        }
        break;
    }
    default:
        break;
    }
    return true;
}
