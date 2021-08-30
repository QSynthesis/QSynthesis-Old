#ifndef OTOCHANGEOPERATION_H
#define OTOCHANGEOPERATION_H

#include "../OtoOperation.h"

class OtoChangeOperation : public OtoOperation {
public:
    OtoChangeOperation();

    QGenonSettings origin() const;
    void setOrigin(const QGenonSettings &origin);

    QGenonSettings modified() const;
    void setModified(const QGenonSettings &modified);

    bool differ() const;

private:
    QGenonSettings m_origin;
    QGenonSettings m_modified;
};

#endif // OTOCHANGEOPERATION_H
