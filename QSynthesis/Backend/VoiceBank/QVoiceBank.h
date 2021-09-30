#ifndef QVOICEBANK_H
#define QVOICEBANK_H

#include "Document/VoiceInfo.h"
#include "QOtoIni.h"
#include "QOtoSampleList.h"
#include "QPrefixMap.h"
#include "QReadmeText.h"

class QVoiceBank : public QObject, public VoiceInfo {
    Q_OBJECT
public:
    explicit QVoiceBank(QObject *parent = nullptr);
    explicit QVoiceBank(const QString &dir, QObject *parent = nullptr);
    ~QVoiceBank();

public:
    bool restore();

    QReadmeText ReadmeTxt;
    QPrefixMap PrefixMap;
    QMap<QString, QOtoIni> OtoInis;

protected:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;
    void prepareCore() override;

private:
    void init();

private:
    bool loadOto();
    bool saveOto();
    bool restoreOto();
    void clearOto();
};

#endif // QVOICEBANK_H
