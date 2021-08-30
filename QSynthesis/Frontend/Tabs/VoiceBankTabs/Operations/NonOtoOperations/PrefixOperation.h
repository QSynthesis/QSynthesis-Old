#ifndef PREFIXOPERATION_H
#define PREFIXOPERATION_H

#include "../NonOtoOperation.h"

class PrefixOperation : public NonOtoOperation {
public:
    PrefixOperation();
    PrefixOperation(Qs::PrefixMap prefixType);

    int noteNum() const;
    void setNoteNum(int noteNum);

    QString origin() const;
    void setOrigin(const QString &origin);

    QString modified() const;
    void setModified(const QString &modified);

    Qs::PrefixMap prefixType() const;
    void setPrefixType(Qs::PrefixMap prefixType);

    bool differ() const override;

private:
    int m_noteNum;

    QString m_origin;
    QString m_modified;

    Qs::PrefixMap m_prefixType;
};

#endif // PREFIXOPERATION_H
