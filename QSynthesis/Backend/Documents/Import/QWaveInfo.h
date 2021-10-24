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

    double duration() const;

    quint32 totalSample() const;
    quint32 bitPerSample() const;
    quint32 dataNum() const;

    quint32 sampleRate() const;
    quint16 channels() const;
    quint16 bytesPerSample() const;

    quint16 blockAlign() const;

    const QVector<qint32> &channel1() const;
    const QVector<qint32> &channel2() const;

    const QByteArray &data() const;

private:
    AudioFormat m_audioFormat;

    quint16 m_channels;

    quint16 m_blockAlign;
    quint16 m_bitsPerSample;

    quint32 m_sampleRate;
    quint32 m_byteRate;
    quint32 m_dataLength;

    QByteArray m_data;

    QVector<qint32> m_channel1;
    QVector<qint32> m_channel2;

    void toChannel1();
    void toChannel2();
};

#endif // QWAVEINFO_H
