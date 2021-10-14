#ifndef POINTSOPERATION_H
#define POINTSOPERATION_H

#include "PropsOperation.h"
#include "QControlPoint.h"

class PointsOperation : public PropsOperation<QList<QControlPoint>> {
public:
    PointsOperation(bool mode2);
    ~PointsOperation();
};

#endif // POINTSOPERATION_H
