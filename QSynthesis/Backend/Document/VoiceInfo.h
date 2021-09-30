#ifndef VOICEINFO_H
#define VOICEINFO_H

#include "Files/BaseDirInfo.h"
#include "Macros.h"

// Brief Information of Voice Database
class VoiceInfo : public BaseDirInfo {
    Q_CHARSET
public:
    VoiceInfo();
    VoiceInfo(const QString &dirname);
    ~VoiceInfo();

protected:
    VoiceInfo(Qs::VariableSource source);

private:
    void init();

public:
    QString name() const;
    QString title() const;
    QString author() const;
    QString avatar() const;
    QString sprite() const;

    void setName(const QString &name);
    void setAuthor(const QString &author);
    void setAvatar(const QString &avatar);
    void setSprite(const QString &sprite);

protected:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;

protected:
    QString m_name;
    QString m_author;
    QString m_avatar;
    QString m_sprite;

    QStringList m_custom; // Other information which can't be edited

private:
    QString infoFilename() const override;
};

#endif // VOICEINFO_H
