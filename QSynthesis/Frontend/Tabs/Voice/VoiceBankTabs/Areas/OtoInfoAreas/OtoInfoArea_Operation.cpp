#include "../../Operations/NonOtoOperations/InfoTextOperation.h"
#include "../../Operations/NonOtoOperations/PrefixOperation.h"
#include "../../VoiceBankGroup.h"
#include "../OtoInfoArea.h"

void OtoInfoArea::saveOperation(NonOtoOperation *no) {
    no = static_cast<NonOtoOperation *>(no->simplify(no));
    if (no) {
        m_ptrs->tab->addHistory(no);
    } else {
        qDebug() << "[NonOtoOperation]"
                 << "Addition Refused";
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
        infoTabs->setCurrentWidget(prefixTab);
        locatePrefix(noteNum);
        break;
    }
    case NonOtoOperation::InfoText: {
        InfoTextOperation *io = static_cast<InfoTextOperation *>(no);
        QString value = undo ? io->origin() : io->modified();
        switch (io->property()) {
        case InfoTextOperation::Readme:
            setText(value);
            infoTabs->setCurrentWidget(readmeTab);
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
        case InfoTextOperation::Sprite:
            if (value.isEmpty()) {
                resetSprite();
            } else if (!setSprite(value)) {
                // QMessageBox::warning(nullptr, MainTitle, tr("This avatar file is
                // deleted.")); return false;
            }
            infoTabs->setCurrentWidget(imageTab);
            break;
        }
        break;
    }
    default:
        break;
    }
    return true;
}
