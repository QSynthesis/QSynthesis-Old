#ifndef SEQUENCEOPERATION_H
#define SEQUENCEOPERATION_H

#include "Note/QLinkNote.h"
#include "NoteOperation.h"

class SequenceOperation : public NoteOperation {
public:
    SequenceOperation(bool increase);
    ~SequenceOperation();

    QList<QLinkNote> notes() const;
    void setNotes(const QList<QLinkNote> &notes);

    virtual bool differ() const override;

private:
    QList<QLinkNote> m_notes;
};

#endif // SEQUENCEOPERATION_H
