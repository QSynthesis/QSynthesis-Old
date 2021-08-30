#ifndef QOTOINI_H
#define QOTOINI_H

#include "File/FileManager.h"
#include "QOtoSampleList.h"

class QOtoIni : public FileManager {
    Q_OBJECT
public:
    explicit QOtoIni(QObject *parent = nullptr);
    explicit QOtoIni(const QString &filename, QObject *parent = nullptr);
    ~QOtoIni();

    QOtoSampleList OtoSamples;

private:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;

private:
    QTextCodec *m_codec;

private:
    static QTextCodec *defaultCodec;

public:
    static QTextCodec *codeForDefault();
    static void setCodeForDefault(QTextCodec *codec);
};

#endif // QOTOINI_H
