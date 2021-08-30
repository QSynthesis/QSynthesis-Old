#include "PlainTextFile.h"
#include "Utils/CharsetHandler.h"

PlainTextFile::PlainTextFile(QObject *parent) : NormalFile(parent) {
    m_codec = nullptr;
}

PlainTextFile::PlainTextFile(const QString &filename, QObject *parent)
    : NormalFile(filename, parent) {
    m_codec = nullptr;
}

PlainTextFile::~PlainTextFile() {
}

bool PlainTextFile::loadCore(bool *valid) {
    bool res = NormalFile::loadCore(valid);

    if (!res) {
        return false;
    }

    QString charset = CharsetHandler::detectCharset(m_data);
    QTextStream in(&m_data);

    if (!charset.isEmpty()) {
        m_codec = QTextCodec::codecForName(charset.toLatin1());
    }
    in.setCodec(m_codec);

    m_text = in.readAll();

    return true;
}

bool PlainTextFile::saveCore() {
    m_data.clear();

    QTextStream out(&m_data);
    out.setCodec(m_codec);
    out << m_text;

    return NormalFile::saveCore();
}

void PlainTextFile::resetCore() {
    NormalFile::resetCore();
    m_text.clear();
}

QString PlainTextFile::text() const {
    return m_text;
}

void PlainTextFile::setText(const QString &text) {
    m_text = text;
}

QTextCodec *PlainTextFile::codec() const {
    return m_codec;
}

void PlainTextFile::setCodec(QTextCodec *codec) {
    m_codec = codec;
}
