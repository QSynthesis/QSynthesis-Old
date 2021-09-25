#ifndef QOTOINI_H
#define QOTOINI_H

#include "File/FileManager.h"
#include "Macros.h"
#include "QOtoSampleList.h"

class QOtoIni : public FileManager {
    Q_OBJECT
    Q_CHARSET
public:
    explicit QOtoIni(QObject *parent = nullptr);
    explicit QOtoIni(const QString &filename, QObject *parent = nullptr);
    ~QOtoIni();

    QOtoSampleList OtoSamples;

private:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;
};

#endif // QOTOINI_H
