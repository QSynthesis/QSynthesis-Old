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

protected:
    Type m_type;
};

#endif // TUNEOPERATION_H
