#ifndef INFOTEXTOPERATION_H
#define INFOTEXTOPERATION_H

#include "../NonOtoOperation.h"

class InfoTextOperation : public NonOtoOperation {
public:
    enum Property { Readme, Name, Author, Avatar, Sprite };

public:
    InfoTextOperation();
    InfoTextOperation(Property prop);

    QString origin() const;
    void setOrigin(const QString &origin);

    QString modified() const;
    void setModified(const QString &modified);

    Property property() const;
    void setProperty(const Property &property);

    bool differ() const override;

private:
    QString m_origin;
    QString m_modified;

    Property m_property;
};

#endif // INFOTEXTOPERATION_H
