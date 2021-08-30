#include "QWaveInfo.h"
#include "QUtils.h"

QWaveInfo::QWaveInfo() {
    reset();
}

QWaveInfo::~QWaveInfo() {
}

bool QWaveInfo::load(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Wave open failed.";
        return false;
    }

    QDataStream data(&file);

    unsigned char strRiff[4], strWave[4], strFmt[4];
    int32_t totalBytes, infoBytes;
    short audioFormat;

    data.readRawData((char *) strRiff, 4);     // 4
    data.readRawData((char *) &totalBytes, 4); // 8
    data.readRawData((char *) strWave, 4);     // 12 0x0C
    data.readRawData((char *) strFmt, 4);      // 16 0x10
    data.readRawData((char *) &infoBytes, 4);  // 20 0x14

    // Invalid format
    if (memcmp(strRiff, "RIFF", 4) != 0 || memcmp(strWave, "WAVE", 4) != 0 ||
        memcmp(strFmt, "fmt ", 4) != 0 || infoBytes < 16) {
        qDebug() << "Wave format invalid.";
        return false;
    }

    data.readRawData((char *) &audioFormat, 2);      // 22 0x18
    data.readRawData((char *) &m_channels, 2);       // 24 0x1A
    data.readRawData((char *) &m_sampleRate, 4);     // 28 0x1E
    data.readRawData((char *) &m_byteRate, 4);       // 32 0x20
    data.readRawData((char *) &m_blockAlign, 2);     // 34 0x22
    data.readRawData((char *) &m_blockPerSample, 2); // 36 0x24

    data.skipRawData(infoBytes - 16); // Suppose no skip

    // Not PCM
    if (audioFormat != AudioFormat::PCM) {
        qDebug() << "Not PCM.";
        return 0;
    }

    m_audioFormat = AudioFormat::PCM;

    unsigned char strData[4];
    int32_t dataLength;
    bool findData = true;

    while (true) {
        int chunkIDSize = data.readRawData((char *) strData, 4);      // 40 0x28
        int chunkNumSize = data.readRawData((char *) &dataLength, 4); // 44 0x32

        if (chunkIDSize != 4 && chunkNumSize != 4) {
            break;
        }

        // Check chunk id
        QByteArray bytes = QByteArray::fromRawData((char *) strData, 4);
        for (int i = 0; i < bytes.size(); ++i) {
            char ch = bytes.at(i);
            if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' || ch <= 'Z'))) {
                qDebug() << "Invalid chunk id.";
                findData = false;
                break;
            }
        }
        if (!findData) {
            break;
        }

        if (bytes == "data") {
            break;
        } else {
            data.skipRawData(dataLength);
        }
    }

    if (!findData) {
        qDebug() << "Data sign missing.";
        return false;
    }

    m_dataLength = dataLength;

    int bytePerSample = m_blockPerSample / 8;
    int sampleCount = m_dataLength / bytePerSample;

    unsigned char chTemp;
    unsigned short nTemp;

    if (m_channels == 1) // Mono
    {
        m_data.resize(sampleCount);
        if (bytePerSample == 1) {
            for (int i = 0; i < sampleCount; i++) {
                data.readRawData((char *) &chTemp, 1);
                m_data[i] = chTemp - 128;
            }
        } else if (bytePerSample == 2) {
            for (int i = 0; i < sampleCount; i++) {
                data.readRawData((char *) &nTemp, 2);
                m_data[i] = (short) nTemp;
            }
        } else if (bytePerSample == 3) {
            for (int i = 0; i < sampleCount; i++) {
                data.readRawData((char *) &chTemp, 1);
                data.readRawData((char *) &nTemp, 2);
                m_data[i] = chTemp + nTemp;
            }
        } else if (bytePerSample == 4) {
            for (int i = 0; i < sampleCount; i++) {
                data.readRawData((char *) &nTemp, 2);
                m_data[i] = (short) nTemp;
            }
        }
    } else if (m_channels == 2) //	Stereo
    {
        m_data.resize(sampleCount / 2);
        m_data2.resize(sampleCount / 2);
        if (bytePerSample == 1) {
            for (int i = 0; i < sampleCount / 2; i++) {
                data.readRawData((char *) &chTemp, 1);
                m_data[i] = chTemp - 128;

                data.readRawData((char *) &chTemp, 1);
                m_data2[i] = chTemp - 128;
            }
        } else if (bytePerSample == 2) {
            for (int i = 0; i < sampleCount / 2; i++) {
                data.readRawData((char *) &nTemp, 2);
                m_data[i] = nTemp;

                data.readRawData((char *) &nTemp, 2);
                m_data2[i] = nTemp;
            }
        } else if (bytePerSample == 3) {
            for (int i = 0; i < sampleCount / 2; i++) {
                data.readRawData((char *) &chTemp, 1);
                data.readRawData((char *) &nTemp, 2);
                m_data[i] = chTemp + nTemp;

                data.readRawData((char *) &chTemp, 1);
                data.readRawData((char *) &nTemp, 2);
                m_data2[i] = chTemp + nTemp;
            }
        } else if (bytePerSample == 4) {
            for (int i = 0; i < sampleCount / 2; i++) {
                data.readRawData((char *) &nTemp, 2);
                m_data[i] = (short) nTemp;

                data.readRawData((char *) &nTemp, 2);
                m_data2[i] = (short) nTemp;
            }
        }
    }

    return true;
}

void QWaveInfo::reset() {
    m_audioFormat = AudioFormat::Unknown;

    m_channels = 0;
    m_sampleRate = 0;
    m_byteRate = 0;
    m_blockAlign = 0;
    m_blockPerSample = 0;
    m_dataLength = 0;

    m_data.clear();
    m_data2.clear();
}

const QVector<int16_t> &QWaveInfo::data() const {
    return m_data;
}

const QVector<int16_t> &QWaveInfo::data2() const {
    return m_data2;
}

double QWaveInfo::duration() const {
    if (m_sampleRate == 0) {
        return 0;
    }
    return double(m_data.size()) / m_sampleRate;
}

uint32_t QWaveInfo::totalSample() const {
    if (m_blockAlign == 0) {
        return 0;
    }
    return m_dataLength / m_blockAlign;
}

uint32_t QWaveInfo::bitPerSample() const {
    if (m_channels == 0) {
        return 0;
    }
    return m_blockPerSample / m_channels;
}

uint32_t QWaveInfo::dataNum() const {
    return totalSample() * bitPerSample() / 16;
}

uint16_t QWaveInfo::channels() const {
    return m_channels;
}

uint16_t QWaveInfo::bytePerSample() const {
    return m_blockPerSample / 8;
}
