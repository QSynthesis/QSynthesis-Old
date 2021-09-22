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

    Operation *next() const;
    void setNext(Operation *next);
    void setTail(Operation *next);

    virtual bool differ() const; // Return true if the operation is effective

    static Operation *simplify(Operation *o);

protected:
    QString m_desc;

    Operation *m_next;
};

#endif // OPERATION_H
