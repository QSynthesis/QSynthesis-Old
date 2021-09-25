#ifndef QPREFIXMAP_H
#define QPREFIXMAP_H

#include <QFile>
#include <QMap>
#include <QObject>
#include <QTextStream>

#include "File/FileManager.h"
#include "Macros.h"
#include "QUtauUtils.h"

class QPrefixMap : public FileManager {
    Q_OBJECT
    Q_CHARSET
public:
    explicit QPrefixMap(QObject *parent = nullptr);
    explicit QPrefixMap(const QString &filename, QObject *parent = nullptr);
    ~QPrefixMap();

    QString PrefixedLyric(int oNoteNum, const QString &oLyric) const;
    bool isEmpty() const;

    QMap<int, QString> PrefixMap;
    QMap<int, QString> SuffixMap;

private:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;
};

#endif // QPREFIXMAP_H
