#ifndef TRACKMODIFYOPERATION_H
#define TRACKMODIFYOPERATION_H

#include "../TrackOperation.h"

class TrackModifyOperation : public TrackOperation {
public:
    enum Change { Resampler, Flags, Name, VoiceDatabase };

    TrackModifyOperation(Change change);

    QString origin() const;
    void setOrigin(const QString &origin);

    QString modified() const;
    void setModified(const QString &modified);

    Change change() const;

    bool differ() const override;

private:
    QString m_origin;
    QString m_modified;

    Change m_change;
};

#endif // TRACKMODIFYOPERATION_H
