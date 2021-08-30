#ifndef TUNEOPERATION_H
#define TUNEOPERATION_H

#include "Operation.h"

class TuneOperation : public Operation {
public:
    TuneOperation();
    virtual ~TuneOperation();

    enum Type { Unknown, Note, Track, Project };

    Type type() const;

    TuneOperation *next() const;
    void setNext(TuneOperation *next);

protected:
    Type m_type;
    TuneOperation *m_next;
};

#endif // TUNEOPERATION_H
