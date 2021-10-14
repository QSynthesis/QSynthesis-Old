#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

#include "MoreWidget.h"

class BaseInterface : public MoreWidget {
    Q_OBJECT
public:
    explicit BaseInterface(QWidget *parent = nullptr);
    virtual ~BaseInterface();
};

#endif // BASEINTERFACE_H
