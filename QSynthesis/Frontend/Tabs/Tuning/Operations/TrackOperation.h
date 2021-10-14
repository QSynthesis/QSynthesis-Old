#ifndef TRACKOPERATION_H
#define TRACKOPERATION_H

#include "TuneOperation.h"

class TrackOperation : public TuneOperation {
public:
    enum Type { Unknown, Add, Remove, Modify, Switch };

    TrackOperation();
    virtual ~TrackOperation();

    Type type() const;
    void setType(const Type &type);

    int index() const;
    void setIndex(int index);

protected:
    Type m_typeT;

    int m_index;
};

#endif // TRACKOPERATION_H
