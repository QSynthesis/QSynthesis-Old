#include "QWavetool.h"
#include "QUtils.h"

#include "Tuning/Controllers/EnvelopeHandler.h"

QWavetool::QWavetool() {
}

QWavetool::~QWavetool() {
}

WavtoolArgs QWavetool::args() const {
    return m_args;
}

void QWavetool::setArgs(const WavtoolArgs &args) {
    m_args = args;
}

bool QWavetool::load() {
    return m_wave.load(m_args.inFile());
}

void QWavetool::clear() {
    m_wave.reset();
}

QByteArray QWavetool::truncatedData() const {
    double unit = 120.0 / m_args.tempo() / 0.96;
    double duration = m_args.length() * unit + m_args.correction();

    QByteArray data;
    data.resize(int(44100 * duration / 1000) * 2);
    data.fill(0);

    quint32 smpRate = m_wave.sampleRate();
    int block = m_wave.blockAlign();
    if (smpRate != 44100 || m_wave.bitPerSample() != 16) {
        return data;
    }

    QByteArray bytes = m_wave.data();

    int frontCut = smpRate * m_args.startPoint() / 1000;
    int frontCutBytes = frontCut * block;
    if (frontCutBytes < 0) {
        QByteArray bytes2;
        bytes2.resize(frontCutBytes);
        bytes2.fill(0);
        bytes.append(bytes2);
    } else {
        if (bytes.size() < frontCutBytes) {
            return data;
        }
        bytes.remove(0, frontCutBytes);
    }

    int samples = smpRate * duration / 1000;
    int sampleBytes = samples * block;

    if (bytes.size() < sampleBytes) {
        QByteArray bytes2;
        bytes2.resize(sampleBytes - bytes.size());
        bytes2.fill(0);
        bytes.append(bytes2);
    } else {
        bytes.truncate(sampleBytes);
    }

    return bytes;
}

QByteArray QWavetool::processedData() const {
    QByteArray data = truncatedData();

    QVector<QControlPoint> env = m_args.envelope();
    if (env.size() < 4 || env.size() > 5) {
        env = EnvelopeHandler::defaultEnvelope.toVector();
    }
    int p3 = (env.size() >= 4) ? (env.size() - 2) : env.size();

    int i;
    double pos;
    QVector<QPair<int, double>> points2, points3, result;

    pos = 0;
    for (i = 0; i < p3; ++i) {
        int samples = sampleRate() * env[i].mX / 1000;
        pos += samples;
        points2.push_back(qMakePair(pos, env[i].mY / 100));
    }
    pos = data.size() / blockAlign() - 1;
    for (i = env.size() - 1; i >= p3; --i) {
        int samples = sampleRate() * env[i].mX / 1000;
        pos -= samples;
        points3.push_back(qMakePair(pos, env[i].mY / 100));
    }

    for (i = 0; i < points2.size(); ++i) {
        result.push_back(points2[i]);
    }
    for (i = points3.size() - 1; i >= 0; --i) {
        result.push_back(points3[i]);
    }

    result.prepend(qMakePair(0, 0));
    result.append(qMakePair(data.size() / blockAlign() - 1, 0));

    int prev = -1;
    double prevVolume = 0;
    for (i = 0; i < result.size(); ++i) {
        auto pair = result.at(i);
        if (pair.first <= prev) {
            pair.first = prev;
        } else if (pair.first > prev) {
            int start = prev + 1;
            int end = pair.first;
            double delta = (pair.second - prevVolume) / (end - start + 1);
            double vol = prevVolume;
            for (int i = start; i <= end; ++i) {
                vol += delta;
                QByteArray sample = data.mid(i * blockAlign(), blockAlign());
                short num = *(short *) sample.data();
                num *= vol;
                data.replace(i * blockAlign(), blockAlign(), QByteArray((char *) &num, 2));
            }
        }
        prev = pair.first;
        prevVolume = pair.second;
    }

    return data;
}

quint32 QWavetool::sampleRate() const {
    return 44100;
}

quint16 QWavetool::blockAlign() const {
    return 2;
}

QByteArray QWavetool::truncateWave(const QString &filename, double begin, double end) {
    QWaveInfo wave;
    if (!wave.load(filename)) {
        return {};
    }

    quint32 smpRate = wave.sampleRate();
    int block = wave.blockAlign();

    QByteArray bytes = wave.data();

    int frontCut = smpRate * begin / 1000;
    int frontCutBytes = frontCut * block;
    if (bytes.size() < frontCutBytes) {
        return {};
    }
    bytes = bytes.mid(frontCutBytes);

    int endCut = smpRate * end / 1000;
    int endCutBytes = endCut * block;
    if (bytes.size() < endCutBytes) {
        return {};
    }
    bytes.chop(endCutBytes);

    return bytes;
}
