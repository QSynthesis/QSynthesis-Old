#ifndef KEYOPERATION_H
#define KEYOPERATION_H

#include "Operation.h"
#include "Types.h"

#include <QKeySequence>
#include <QString>

class KeyOperation : public Operation {
public:
    KeyOperation();
    ~KeyOperation();

    QPair<int, int> index() const;
    void setIndex(const QPair<int, int> &index);

    QString origin() const;
    void setOrigin(const QString &origin);

    QString modified() const;
    void setModified(const QString &modified);

    KeyOperation *next() const;

    virtual bool differ() const; // Return true if the operation is effective

private:
    QPair<int, int> m_index;

    QString m_origin;
    QString m_modified;
};

#endif // KEYOPERATION_H
