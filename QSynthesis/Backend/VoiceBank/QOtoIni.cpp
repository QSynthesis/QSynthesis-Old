#include "QOtoIni.h"
#include "QUtauUtils.h"
#include "QUtils.h"
#include "Utils/CharsetHandler.h"

Q_CHARSET_DECLARE(QOtoIni)

QOtoIni::QOtoIni(QObject *parent) : FileManager(parent) {
    m_codec = defaultCodec;
    reset();
}

QOtoIni::QOtoIni(const QString &filename, QObject *parent) : FileManager(parent) {
    m_codec = defaultCodec;
    setFilename(filename);
}

QOtoIni::~QOtoIni() {
}

bool QOtoIni::loadCore(bool *valid) {
    QFile file(m_filename);

    if (!file.exists()) {
        return true;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QByteArray data = file.readAll();

    // Detect Code
    QString charset = CharsetHandler::detectCharset(data);
    QTextStream in(&data);

    if (!charset.isEmpty()) {
        m_codec = QTextCodec::codecForName(charset.toLatin1());
    }

    in.setCodec(m_codec);

    QString line;

    // Load oto
    QString alias;
    QString filename;
    QString fileBody;
    QVector<QString> namesStrs;
    QVector<QString> settingsStrs;

    QString dirname = PathFindUpper(m_filename);

    while (!in.atEnd()) {
        line = in.readLine();

        if (line.isEmpty()) {
            continue;
        }

        settingsStrs = qstring_to_qvector_qstring(line);
        namesStrs = qstring_to_qvector_qstring(settingsStrs[0], "=");

        if (namesStrs.size() >= 2) {
            alias = namesStrs[1];
        } else {
            alias = "";
        }

        filename = namesStrs[0];
        fileBody = filename.mid(0, namesStrs[0].lastIndexOf("."));
        settingsStrs.resize(6);

        QGenonSettings aGenon;
        QString absoluteFileName = filename;
        if (isPathRelative(filename)) {
            absoluteFileName = dirname + Slash + filename;
        }
        aGenon.mFileName = absoluteFileName;
        aGenon.mAlias = alias;
        aGenon.mOffset = settingsStrs[1].toDouble();
        aGenon.mConstant = settingsStrs[2].toDouble();
        aGenon.mBlank = settingsStrs[3].toDouble();
        aGenon.mPreUtterance = settingsStrs[4].toDouble();
        aGenon.mVoiceOverlap = settingsStrs[5].toDouble();

        OtoSamples.insertAuto(aGenon);
    }

    file.close();
    return true;
}

bool QOtoIni::saveCore() {
    QFile file(m_filename);

    // Delete when empty
    if (OtoSamples.isEmpty()) {
        if (file.exists()) {
            return file.remove();
        } else {
            return true;
        }
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out.setCodec(m_codec);

    for (auto it = OtoSamples.begin(); it != OtoSamples.end(); ++it) {
        const QList<QGenonSettings> &sample = *it;
        for (auto it = sample.begin(); it != sample.end(); ++it) {
            const QGenonSettings &line = *it;
            out << PathFindFileName(line.mFileName) << '=';
            out << line.mAlias << ',';
            out << line.mOffset << ',';
            out << line.mConstant << ',';
            out << line.mBlank << ',';
            out << line.mPreUtterance << ',';
            out << line.mVoiceOverlap << Qt::endl;
        }
    }

    file.close();
    return true;
}

void QOtoIni::resetCore() {
    OtoSamples.clear();
}
