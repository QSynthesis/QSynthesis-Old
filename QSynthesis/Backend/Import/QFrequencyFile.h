#ifndef QFREQUENCYFILE_H
#define QFREQUENCYFILE_H

#include <QDebug>
#include <QFile>

class QFrequencyFile {
public:
    QFrequencyFile();
    ~QFrequencyFile();
    void reset();

    bool load(const QString &filename);
    bool save(const QString &filename);

    QList<double> Amplitude;
    QList<double> Frequency;

    unsigned SamplesPerFrq;
    double AverageFrq;
};

#endif // QFREQUENCYFILE_H
