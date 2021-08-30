#ifndef VOICECOLLECT_H
#define VOICECOLLECT_H

#include "DirectoryCollect.h"
#include "VoiceInfo.h"

// app/voice
class VoiceCollect : public DirectoryCollect {
    Q_OBJECT
public:
    explicit VoiceCollect(QObject *parent = nullptr);
    explicit VoiceCollect(QString dir, QObject *parent = nullptr);

    QList<VoiceInfo *> dirs() const;

private:
    DirectoryManager *addDirCore(const QString &dir, bool init) override;
    void handleChildChanged();
};


#endif // VOICECOLLECT_H
