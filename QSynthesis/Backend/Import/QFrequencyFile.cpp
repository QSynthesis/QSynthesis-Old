#include "QFrequencyFile.h"

#include <QDataStream>

QFrequencyFile::QFrequencyFile() {
    reset();
}

QFrequencyFile::~QFrequencyFile() {
}

void QFrequencyFile::reset() {
    Amplitude.clear();
    Frequency.clear();

    SamplesPerFrq = 0;
    AverageFrq = 0;
}

bool QFrequencyFile::load(const QString &filename) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QDataStream data(&file);
    char prefix[8];

    data.readRawData(prefix, 8); // 0x8

    if (memcmp(prefix, "FREQ0003", 8) != 0) {
        return false;
    }

    data.readRawData((char *) &SamplesPerFrq, 4); // 0xC
    data.readRawData((char *) &AverageFrq, 8);    // 0x14

    data.skipRawData(16); // 0x24 Empty data

    uint32_t numChunks;
    data.readRawData((char *) &numChunks, 4); // 0x28

    for (uint32_t i = 0; i < numChunks; ++i) {
        double frq;
        double amp;

        data.readRawData((char *) &frq, 8);
        data.readRawData((char *) &amp, 8);

        Frequency.append(frq);
        Amplitude.append(amp);
    }
    file.close();
    return true;
}

bool QFrequencyFile::save(const QString &filename) {
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QDataStream data(&file);
    data.writeRawData("FREQ003", 8);               // 0x8
    data.writeRawData((char *) &SamplesPerFrq, 4); // 0xC
    data.writeRawData((char *) &AverageFrq, 8);    // 0x14

    // Skip 16 unit
    for (uint32_t i = 0; i < 16; ++i) {
        data.writeRawData(0, 1); // 0x24
    }

    unsigned numChunks = Frequency.size();
    data.writeRawData((char *) &numChunks, 4); // 0x28

    for (uint32_t i = 0; i < numChunks; ++i) {
        double frq = Frequency.at(i);
        double amp = Amplitude.at(i);

        data.writeRawData((char *) &frq, 8);
        data.writeRawData((char *) &amp, 8);
    }
    file.close();
    return true;
}
