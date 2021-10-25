#include "QReadmeText.h"
#include "QUtauBasic.h"
#include "QUtauStrCore.h"
#include "SystemApis.h"

#include <QFile>
#include <QTextCodec>
#include <QTextStream>

using namespace UtaFilenames;

Q_CHARSET_STATIC_DECLARE(QReadmeText)

QReadmeText::QReadmeText() : BaseDirInfo(Qs::Default) {
    m_codec = defaultCodec;
}

QReadmeText::QReadmeText(const QString &dirname) : BaseDirInfo(Qs::Default) {
    m_codec = defaultCodec;
    setDirname(dirname);
}

QReadmeText::~QReadmeText() {
}

bool QReadmeText::fromLocalFile(const QString &filename) {
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

    Text = m_codec->toUnicode(data);
    return true;
}

bool QReadmeText::toLocalFile(const QString &filename) {
    QFile file(filename);
    QByteArray data;

    // Delete when empty
    if (Text.isEmpty()) {
        if (file.exists()) {
            return file.remove();
        } else {
            return true;
        }
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    file.write(m_codec->fromUnicode(Text));
    file.close();
    return true;
}

bool QReadmeText::loadCore(bool *valid) {
    return fromLocalFile(filename());
}

bool QReadmeText::saveCore() {
    return toLocalFile(filename());
}

void QReadmeText::resetCore() {
    Text.clear();
}

QString QReadmeText::infoFilename() const {
    return FILE_NAME_VOICE_README;
}
