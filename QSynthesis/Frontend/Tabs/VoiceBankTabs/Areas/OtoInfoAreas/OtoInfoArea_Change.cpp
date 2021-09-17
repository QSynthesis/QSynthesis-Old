#include "../../Operations/NonOtoOperations/InfoTextOperation.h"
#include "../../Operations/NonOtoOperations/PrefixOperation.h"
#include "../OtoInfoArea.h"

void OtoInfoArea::handleNameChanged() {
    QString name = lcName->getValue();

    InfoTextOperation *io = new InfoTextOperation(InfoTextOperation::Name);
    io->setOrigin(m_name);
    io->setModified(name);

    // Change backend value
    m_name = name;

    // Save Opeartion
    saveOperation(io);
}

void OtoInfoArea::handleAuthorChanged() {
    QString author = lcAuthor->getValue();

    InfoTextOperation *io = new InfoTextOperation(InfoTextOperation::Author);
    io->setOrigin(m_author);
    io->setModified(author);

    // Change backend value
    m_author = author;

    // Save Opeartion
    saveOperation(io);
}

void OtoInfoArea::handlePrefixChanged(int noteNum, QString value) {
    PrefixOperation *p = new PrefixOperation(Qs::Prefix);

    auto it = m_prefixMap.find(noteNum);

    p->setNoteNum(noteNum);
    p->setOrigin(it == m_prefixMap.end() ? "" : it.value());
    p->setModified(value);

    // Change backend value
    m_prefixMap[noteNum] = value;
    // Save Opeartion
    saveOperation(p);
}

void OtoInfoArea::handleSuffixChanged(int noteNum, QString value) {
    PrefixOperation *p = new PrefixOperation(Qs::Suffix);

    auto it = m_suffixMap.find(noteNum);

    p->setNoteNum(noteNum);
    p->setOrigin(it == m_suffixMap.end() ? "" : it.value());
    p->setModified(value);

    // Change backend value
    m_suffixMap[noteNum] = value;
    // Save Opeartion
    saveOperation(p);
}

void OtoInfoArea::handleTextChanged(QString text) {
    InfoTextOperation *io = new InfoTextOperation(InfoTextOperation::Readme);

    io->setOrigin(m_text);
    io->setModified(text);

    // Change backend value
    m_text = text;

    // Save Opeartion
    saveOperation(io);
}

void OtoInfoArea::handleAvatarChanged(QString modified, QString origin) {
    InfoTextOperation *io = new InfoTextOperation(InfoTextOperation::Avatar);

    io->setOrigin(origin);
    io->setModified(modified);

    // Save Opeartion
    saveOperation(io);
}
