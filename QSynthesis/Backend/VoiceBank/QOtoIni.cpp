#include "QOtoIni.h"
#include "NormalFile.h"
#include "QUtauStrings.h"
#include "QUtauUtils.h"
#include "QUtils.h"
#include "Utils/CharsetHandler.h"

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
    NormalFile file(filename);
    if (!file.exists()) {
        return true;
    }
    if (!file.load()) {
        return false;
    }

    QByteArray data = file.data();

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
    QString fileName;
    QString fileBody;
    QVector<QString> namesStrs;
    QVector<QString> settingsStrs;

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

        fileName = namesStrs[0];
        fileBody = fileName.mid(0, namesStrs[0].lastIndexOf("."));
        settingsStrs.resize(6);

        QGenonSettings aGenon;
        QString absoluteFileName = fileName;
        if (isPathRelative(fileName)) {
            absoluteFileName = dirname() + Slash + fileName;
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

    return true;
}

bool QOtoIni::toLocalFile(const QString &filename) {
    NormalFile file(filename);

    // Delete when empty
    if (OtoSamples.isEmpty()) {
        if (file.exists()) {
            return file.remove();
        } else {
            return true;
        }
    }

    QByteArray data;
    QTextStream out(&data);
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

    file.setData(data);
    return file.save();
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
