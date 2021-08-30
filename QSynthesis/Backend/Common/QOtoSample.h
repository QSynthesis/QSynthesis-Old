#ifndef QOTOSAMPLE_H
#define QOTOSAMPLE_H

#include "QGenonSettings.h"

#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QVector>

class QOtoSample : public QList<QGenonSettings> {
public:
    QOtoSample();
    QOtoSample(const QString &filename);

    QString filename() const;
    void setFilename(const QString &filename);

    void setData(QList<QGenonSettings> &&sample);
    void setData(const QList<QGenonSettings> &sample);

    const QList<QGenonSettings> &data() const;

    void clearAll();

    bool valid() const;
    bool frqExist() const;
    bool mrqExist() const;

private:
    QString m_filename;

public:
    bool operator==(const QOtoSample &sample) const;
    bool operator!=(const QOtoSample &sample) const;
    bool operator<(const QOtoSample &sample) const;

    friend uint qHash(const QOtoSample &samples, uint seed);
};

#endif // QOTOSAMPLE_H
