#ifndef OPERATION_H
#define OPERATION_H

#include <QDebug>
#include <QObject>

#include "Types.h"

class Operation {
public:
    explicit Operation();
    virtual ~Operation();

    QString desc() const;
    void setDesc(const QString &desc);

    virtual bool differ() const; // Return true if the operation is effective

private:
    QString m_desc;
};

#endif // OPERATION_H
