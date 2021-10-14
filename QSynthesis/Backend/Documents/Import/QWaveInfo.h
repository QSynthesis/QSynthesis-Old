#ifndef QWAVEINFO_H
#define QWAVEINFO_H

#include <QDataStream>
#include <QDebug>
#include <QFile>

class QWaveInfo {
public:
    enum AudioFormat {
        Unknown,
        PCM = 0x1,
        MS_ADPCM = 0x2,
        IEEE = 0x3,
        ALAW = 0x6,
        AULAW = 0x7,
        IMA_ADPCM = 0x17,
        ITU_G_723 = 0x20,
        ITU_G_721 = 0x49,
        MPEG = 0x80,
    };

    QWaveInfo();
    ~QWaveInfo();

    bool load(const QString &filename);
    void reset();

    bool isEmpty() const;

    const QVector<qint16> &data() const;
    const QVector<qint16> &data2() const;
    double duration() const;

    quint32 totalSample() const;
    quint32 bitPerSample() const;
    quint32 dataNum() const;

    quint32 sampleRate() const;
    quint16 channels() const;
    quint16 bytePerSample() const;

private:
    AudioFormat m_audioFormat;

    quint16 m_channels;

    quint16 m_blockAlign;
    quint16 m_blockPerSample;

    quint32 m_sampleRate;
    quint32 m_byteRate;
    quint32 m_dataLength;

    QVector<qint16> m_data;
    QVector<qint16> m_data2;
};

#endif // QWAVEINFO_H
