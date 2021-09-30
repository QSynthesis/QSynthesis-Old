#include "QReadmeText.h"
#include "Files/NormalFile.h"
#include "QUtauStrings.h"
#include "Utils/CharsetHandler.h"

#include <QTextCodec>
#include <QTextStream>

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
    if (!charset.isEmpty()) {
        m_codec = QTextCodec::codecForName(charset.toLatin1());
    }
    Text = m_codec->toUnicode(data);
    return true;
}

bool QReadmeText::toLocalFile(const QString &filename) {
    NormalFile file(filename);

    // Delete when empty
    if (Text.isEmpty()) {
        if (file.exists()) {
            return file.remove();
        } else {
            return true;
        }
    }
    file.setData(m_codec->fromUnicode(Text));
    return file.save();
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
