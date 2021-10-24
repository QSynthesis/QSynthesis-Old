#ifndef QWAVETOOL_H
#define QWAVETOOL_H

#include "QWaveInfo.h"
#include "Structures/Render/WavtoolArgs.h"

class QWavetool {
public:
    QWavetool();
    ~QWavetool();

public:
    WavtoolArgs args() const;
    void setArgs(const WavtoolArgs &args);

    bool load();
    void clear();

    QByteArray truncatedData() const;
    QByteArray processedData() const;

    quint32 sampleRate() const;
    quint16 bytesPerSample() const;
    quint16 blockAlign() const;

    static QByteArray truncateWave(const QString &filename, double begin, double end);

private:
    QWaveInfo m_wave;
    WavtoolArgs m_args;
};

#endif // QWAVETOOL_H
