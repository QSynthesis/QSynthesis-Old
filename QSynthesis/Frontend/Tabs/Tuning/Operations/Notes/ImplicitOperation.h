#ifndef IMPLICITOPERATION_H
#define IMPLICITOPERATION_H

#include "PropsOperation.h"

class ImplicitOperation :public PropsOperation<QString> {
public:
    ImplicitOperation(Type type);
    ~ImplicitOperation();
};

#endif // IMPLICITOPERATION_H
