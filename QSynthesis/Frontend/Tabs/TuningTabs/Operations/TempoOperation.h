#ifndef TEMPOOPERATION_H
#define TEMPOOPERATION_H

#include "NoteOperation.h"

class TempoOperation : public NoteOperation {
public:
    TempoOperation();

    double origin() const;
    void setOrigin(double origin);

    double modified() const;
    void setModified(double modified);

    bool orgStatus() const;
    void setOrgStatus(bool orgStatus);

    bool newStatus() const;
    void setNewStatus(bool newStatus);

    bool differ() const override;

    int index() const;
    void setIndex(int index);

private:
    int m_index;

    double m_origin;
    double m_modified;

    bool m_orgStatus;
    bool m_newStatus;

    void init();
};

#endif // TEMPOOPERATION_H
