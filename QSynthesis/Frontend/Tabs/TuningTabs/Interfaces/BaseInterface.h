#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

#include <QWidget>

class BaseInterface : public QWidget {
    Q_OBJECT
public:
    explicit BaseInterface(QWidget *parent = nullptr);
    virtual ~BaseInterface();
};

#endif // BASEINTERFACE_H
