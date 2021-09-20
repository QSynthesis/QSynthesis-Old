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

    Qs::IgnoreSelection ignore() const;
    void setIgnore(const Qs::IgnoreSelection &ignore);

private:
    QList<QLinkNote> m_notes;
    Qs::IgnoreSelection m_ignore;
};

#endif // SEQUENCEOPERATION_H
