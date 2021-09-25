#ifndef VOICEINFO_H
#define VOICEINFO_H

#include "DirectoryManager.h"
#include "File/NormalFile.h"

// Brief Information of Voice Database
class VoiceInfo : public DirectoryManager {
    Q_OBJECT
    Q_CHARSET
public:
    explicit VoiceInfo(QObject *parent = nullptr);
    explicit VoiceInfo(const QString &dir, QObject *parent = nullptr);
    ~VoiceInfo();

    bool valid() const;

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
    virtual bool loadCore() override;
    virtual bool saveCore() override;

    virtual void resetCore() override;
    virtual void prepareCore() override;

    bool loadCharTxt();
    bool saveCharTxt();

protected:
    NormalFile charTxt;

    QString m_name;
    QString m_author;
    QString m_avatar;
    QString m_sprite;

    QStringList m_custom; // Other information which can't be edited

private:
    void init();

    void handleChangedCore() override;
    void handleCharTxtChanged();

signals:
    void charTxtChanged();
};

#endif // VOICEINFO_H
