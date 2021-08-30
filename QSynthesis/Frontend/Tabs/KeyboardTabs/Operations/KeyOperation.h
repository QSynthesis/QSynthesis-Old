#ifndef KEYOPERATION_H
#define KEYOPERATION_H

#include "Operation.h"

#include <QKeySequence>
#include <QString>

class KeyOperation : public Operation {
public:
    KeyOperation();

    int id() const;
    void setId(int id);

    QString origin() const;
    void setOrigin(const QString &origin);

    QString modified() const;
    void setModified(const QString &modified);

    virtual bool differ() const; // Return true if the operation is effective

private:
    int m_id;

    QString m_origin;
    QString m_modified;
};

#endif // KEYOPERATION_H
