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

    const QVector<int16_t> &data() const;
    const QVector<int16_t> &data2() const;
    double duration() const;

    uint32_t totalSample() const;
    uint32_t bitPerSample() const;
    uint32_t dataNum() const;

    uint16_t channels() const;
    uint16_t bytePerSample() const;

private:
    AudioFormat m_audioFormat;

    uint16_t m_channels;

    uint16_t m_blockAlign;
    uint16_t m_blockPerSample;

    uint32_t m_sampleRate;
    uint32_t m_byteRate;
    uint32_t m_dataLength;

    QVector<int16_t> m_data;
    QVector<int16_t> m_data2;
};

#endif // QWAVEINFO_H
