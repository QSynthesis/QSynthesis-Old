#ifndef QREADMETEXT_H
#define QREADMETEXT_H

#include "BaseDirInfo.h"
#include "Macros.h"

class QReadmeText : public BaseDirInfo {
    Q_CHARSET
public:
    QReadmeText();
    QReadmeText(const QString &dirname);
    virtual ~QReadmeText();

    QString Text;

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

#endif // QREADMETEXT_H
