#ifndef QVOICEBANK_H
#define QVOICEBANK_H

#include "Directory/VoiceInfo.h"
#include "QOtoLevel.h"
#include "QPrefixMap.h"
#include "QReadmeText.h"

class QVoiceBank : public VoiceInfo {
    Q_OBJECT
public:
    explicit QVoiceBank(QObject *parent = nullptr);
    explicit QVoiceBank(const QString &dir, QObject *parent = nullptr);
    ~QVoiceBank();

public:
    bool restore();

    QReadmeText ReadmeTxt;
    QPrefixMap PrefixMap;
    QOtoLevel OtoRoot;

    QMap<QString, QOtoLevel *> OtoLevels;

protected:
    QMap<QString, QOtoSampleList> OtoCache;

    virtual bool loadCore();
    virtual bool saveCore();

    virtual void resetCore();
    virtual void prepareCore();

private:
    void init();

    void handleReadmeTxtChanged();
    void handlePrefixMapChanged();

    void handleLevelCreated(QOtoLevel *level, bool init);
    void handleLevelDestroyed(QOtoLevel *level, bool init);

    void handleLevelChanged(QOtoLevel *level);
    void handleLevelOtoIniChanged(QOtoLevel *level);

private:
    void loadOtoCache(QOtoLevel *level);

    bool loadOto();
    bool saveOto();
    bool restoreOto();
    void clearOto();

signals:
    void readmeTxtChanged();
    void prefixMapChanged();

    void otoDirCreated(QString path);
    void otoDirDestroyed(QString path);

    void otoDirChanged(QString path);
    void otoFileChanged(QString path);
};

#endif // QVOICEBANK_H
