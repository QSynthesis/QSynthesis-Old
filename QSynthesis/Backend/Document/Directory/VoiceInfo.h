#ifndef VOICEINFO_H
#define VOICEINFO_H

#include "DirectoryManager.h"
#include "File/NormalFile.h"

// Brief Information of Voice Database
class VoiceInfo : public DirectoryManager {
    Q_OBJECT
public:
    explicit VoiceInfo(QObject *parent = nullptr);
    explicit VoiceInfo(const QString &dir, QObject *parent = nullptr);
    ~VoiceInfo();

    bool valid() const;

public:
    QTextCodec *codec() const;
    void setCodec(QTextCodec *codec);

public:
    QString name() const;
    QString title() const;
    QString author() const;
    QString image() const;

    void setName(const QString &name);
    void setAuthor(const QString &author);

    void setImage(const QString &image);

protected:
    virtual bool loadCore() override;
    virtual bool saveCore() override;

    virtual void resetCore() override;
    virtual void prepareCore() override;

    bool loadCharTxt();
    bool saveCharTxt();

protected:
    QTextCodec *m_codec;

    NormalFile charTxt;

    QString m_name;
    QString m_author;
    QString m_image;

    QStringList m_custom; // Other information which can't be edited

private:
    void init();

    void handleChangedCore() override;
    void handleCharTxtChanged();

signals:
    void charTxtChanged();

private:
    static QTextCodec *defaultCodec;

public:
    static QTextCodec *codeForDefault();
    static void setCodeForDefault(QTextCodec *codec);
};

#endif // VOICEINFO_H
