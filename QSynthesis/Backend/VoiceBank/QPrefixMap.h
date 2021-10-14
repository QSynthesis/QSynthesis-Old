#ifndef QPREFIXMAP_H
#define QPREFIXMAP_H

#include <QFile>
#include <QMap>
#include <QObject>
#include <QTextStream>

#include "BaseDirInfo.h"
#include "Macros.h"
#include "QUtauUtils.h"

class QPrefixMap : public BaseDirInfo {
    Q_CHARSET
public:
    QPrefixMap();
    QPrefixMap(const QString &filename);
    ~QPrefixMap();

public:
    QString prefixedLyric(int oNoteNum, const QString &oLyric) const;
    bool isEmpty() const;

public:
    bool fromLocalFile(const QString &filename);
    bool toLocalFile(const QString &filename);

protected:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;

private:
    QString infoFilename() const override;

public:
    QMap<int, QString> PrefixMap;
    QMap<int, QString> SuffixMap;
};

#endif // QPREFIXMAP_H
