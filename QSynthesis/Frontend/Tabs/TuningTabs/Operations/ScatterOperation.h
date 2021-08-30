#ifndef SCATTEROPERATION_H
#define SCATTEROPERATION_H

#include "PropsOperation.h"

class ScatterOperation : public PropsOperation<QList<double>> {
public:
    ScatterOperation(bool mode1);
    ~ScatterOperation();
};

#endif // SCATTEROPERATION_H
