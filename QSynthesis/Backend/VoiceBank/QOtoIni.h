#ifndef QOTOINI_H
#define QOTOINI_H

#include "Files/BaseDirInfo.h"
#include "Macros.h"
#include "QOtoSampleList.h"

class QOtoIni : public BaseDirInfo {
    Q_CHARSET
public:
    QOtoIni();
    QOtoIni(const QString &dirname);
    ~QOtoIni();

    QOtoSampleList OtoSamples;

public:
    bool fromLocalFile(const QString &filename);
    bool toLocalFile(const QString &filename);

protected:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;

private:
    QString infoFilename() const override;
};

#endif // QOTOINI_H
