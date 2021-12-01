#include "QOtoIni.h"
#include "QUtauBasic.h"
#include "QUtauStrCore.h"
#include "SystemApis.h"

using namespace Utau;

Q_CHARSET_DECLARE(QOtoIni)

QOtoIni::QOtoIni() : BaseDirInfo(Qs::Default) {
    m_codec = defaultCodec;
    reset();
}

QOtoIni::QOtoIni(const QString &filename) : BaseDirInfo(Qs::Default) {
    m_codec = defaultCodec;
    setDirname(filename);
}

QOtoIni::~QOtoIni() {
}

bool QOtoIni::fromLocalFile(const QString &filename) {
    QFile file(filename);
    QByteArray data;
    if (!file.exists()) {
        return true;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    data = file.readAll();
    file.close();

    QTextCodec *codec = GetUtfCodec(data);
    QTextStream in(&data);
    if (codec) {
        m_codec = codec;
    }
    in.setCodec(m_codec);

    QString line;

    while (!in.atEnd()) {
        line = in.readLine();
        if (line.isEmpty()) {
            continue;
        }
        QGenonSettings genon = Utau::StringToGenon(line);
        genon.mFileName.prepend(dirname() + Slash);
        OtoSamples.insertAuto(genon);
    }

    return true;
}

bool QOtoIni::toLocalFile(const QString &filename) {
    QFile file(filename);
    QByteArray data;

    // Delete when empty
    if (OtoSamples.isEmpty()) {
        if (file.exists()) {
            return file.remove();
        } else {
            return true;
        }
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&data);
    out.setCodec(m_codec);

    for (auto it = OtoSamples.begin(); it != OtoSamples.end(); ++it) {
        const QList<QGenonSettings> &sample = *it;
        for (auto it = sample.begin(); it != sample.end(); ++it) {
            out << Utau::GenonToString(*it) << Qt::endl;
        }
    }

    file.write(data);
    file.close();
    return true;
}

bool QOtoIni::loadCore(bool *valid) {
    return fromLocalFile(filename());
}

bool QOtoIni::saveCore() {
    return toLocalFile(filename());
}

void QOtoIni::resetCore() {
    OtoSamples.clear();
}

QString QOtoIni::infoFilename() const {
    return FILE_NAME_OTO_INI;
}
