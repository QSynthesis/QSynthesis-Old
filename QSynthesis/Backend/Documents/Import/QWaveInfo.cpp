#include "QWaveInfo.h"

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
    qint32 totalBytes, infoBytes;
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

    data.readRawData((char *) &audioFormat, 2);     // 22 0x18
    data.readRawData((char *) &m_channels, 2);      // 24 0x1A
    data.readRawData((char *) &m_sampleRate, 4);    // 28 0x1E
    data.readRawData((char *) &m_byteRate, 4);      // 32 0x20
    data.readRawData((char *) &m_blockAlign, 2);    // 34 0x22
    data.readRawData((char *) &m_bitsPerSample, 2); // 36 0x24

    data.skipRawData(infoBytes - 16); // Suppose no skip

    // Not PCM
    if (audioFormat != AudioFormat::PCM) {
        qDebug() << "Not PCM.";
        return 0;
    }

    m_audioFormat = AudioFormat::PCM;

    unsigned char strData[4];
    qint32 dataLength;
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
            if (!QChar::fromLatin1(bytes.at(i)).isLetter()) {
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

    int bytesPerSample = m_bitsPerSample / 8;
    int sampleCount = m_dataLength / bytesPerSample;

    char *ch = new char[bytesPerSample];
    for (int i = 0; i < sampleCount; i++) {
        data.readRawData(ch, bytesPerSample);
        m_data.append(ch, bytesPerSample);
    }
    delete[] ch;

    toChannel1();
    toChannel2();

    return true;
}

void QWaveInfo::reset() {
    m_audioFormat = AudioFormat::Unknown;

    m_channels = 0;
    m_sampleRate = 0;
    m_byteRate = 0;
    m_blockAlign = 0;
    m_bitsPerSample = 0;
    m_dataLength = 0;

    m_data.clear();
}

bool QWaveInfo::isEmpty() const {
    return m_data.isEmpty();
}

double QWaveInfo::duration() const {
    if (m_sampleRate == 0) {
        return 0;
    }
    return double(m_channel1.size()) / m_sampleRate;
}

quint32 QWaveInfo::totalSample() const {
    if (m_blockAlign == 0) {
        return 0;
    }
    return m_dataLength / m_blockAlign;
}

quint32 QWaveInfo::bitPerSample() const {
    if (m_channels == 0) {
        return 0;
    }
    return m_bitsPerSample / m_channels;
}

quint32 QWaveInfo::dataNum() const {
    return totalSample() * bitPerSample() / 16;
}

quint32 QWaveInfo::sampleRate() const {
    return m_sampleRate;
}

quint16 QWaveInfo::channels() const {
    return m_channels;
}

quint16 QWaveInfo::bytesPerSample() const {
    return m_bitsPerSample / 8;
}

quint16 QWaveInfo::blockAlign() const {
    return m_blockAlign;
}

const QVector<qint32> &QWaveInfo::channel1() const {
    return m_channel1;
}

const QVector<qint32> &QWaveInfo::channel2() const {
    return m_channel2;
}

const QByteArray &QWaveInfo::data() const {
    return m_data;
}

void QWaveInfo::toChannel1() {
    int bytesPerSample = m_bitsPerSample / 8;
    int sampleCount = m_dataLength / bytesPerSample;

    QVector<qint32> data;
    data.resize(sampleCount);

    int i = 0;
    int j = 0;
    while (j < m_data.size() && i < data.size()) {
        QByteArray cur = m_data.mid(j, bytesPerSample);
        if (bytesPerSample == 1) {
            char val = cur.front();
            data[i] = (qint32) val;
        } else if (bytesPerSample == 2) {
            short val = *((short *) cur.data());
            data[i] = val;
        } else if (bytesPerSample == 3) {
            QByteArray temp = cur;
            temp.prepend('\0');
            qint32 val = *((qint32 *) temp.data());
            data[i] = val / 256;
        } else if (bytesPerSample == 4) {
            qint32 val = *((qint32 *) cur.data());
            data[i] = val;
        }

        i++;
        j += m_blockAlign;
    }
    m_channel1 = std::move(data);
}

void QWaveInfo::toChannel2() {
    int bytesPerSample = m_bitsPerSample / 8;
    int sampleCount = m_dataLength / bytesPerSample;

    QVector<qint32> data;
    data.resize(sampleCount);

    int i = 0;
    int j = 0;
    while (i < m_data.size() && i < data.size()) {
        j += bytesPerSample;

        QByteArray cur = m_data.mid(j, bytesPerSample);
        if (bytesPerSample == 1) {
            char val = cur.front();
            data[i] = (qint32) val;
        } else if (bytesPerSample == 2) {
            short val = *((short *) cur.data());
            data[i] = val;
        } else if (bytesPerSample == 3) {
            QByteArray temp = cur;
            temp.prepend('\0');
            qint32 val = *((qint32 *) temp.data());
            data[i] = val / 256;
        } else if (bytesPerSample == 4) {
            qint32 val = *((qint32 *) cur.data());
            data[i] = val;
        }

        i++;
        j += m_blockAlign - bytesPerSample;
    }
    m_channel2 = std::move(data);
}
