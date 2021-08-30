#ifndef QOTOREFERENCE_H
#define QOTOREFERENCE_H

#include <QDir>
#include <QFile>
#include <QObject>

#include "QGenonSettings.h"
#include "QOtoSampleList.h"
#include "QUtauConstants.h"
#include "QUtauUtils.h"

#include "QUtils.h"

class QVoiceBank;

class QOtoReference : public QObject {
    Q_OBJECT
public:
    explicit QOtoReference(QObject *parent = nullptr);
    ~QOtoReference();

    bool fromFiles(const QString &voiceDir);  // Load from file system
    bool fromMemory(const QVoiceBank &voicebank); // Load from existing voicebank tab
    void sendRefresh();

    void clearData();

    QString voiceDir() const;
    QString prefixMapPath() const;

public:
    bool findSample(const QString &oLyric, QGenonSettings *oGenon, int oNoteNum = 0) const;
    QStringList findAliasStartsWith(const QString &prefix) const;

private:
    bool loadOtoIni();
    bool loadPrefixMap();

    void clearOtoIni();
    void clearPrefixMap();

    void registerSamples(const QOtoSampleList &samples);

private:
    QString m_voiceDir;

    QMap<int, QString> prefixMap;
    QMap<int, QString> suffixMap;

    enum otoRegFlags { ofBlank, ofFileName, ofAlias };

    QMap<QString, otoRegFlags> flags;
    QMap<QString, QGenonSettings> genonSettings;

signals:
    void refresh();

    // Static
private:
    static QMap<QString, QPair<int, QOtoReference *>> otoRefMap; // Voice Dir -> (Count, Ref)

public:
    static bool addReference(QString voiceDir, QOtoReference *&oto);
    static bool removeReference(QString voiceDir);

    static QOtoReference *findReference(QString voiceDir);
    static bool refreshReference(QString voiceDir, const QVoiceBank &voicebank);
};

#endif // QOTOREFERENCE_H
