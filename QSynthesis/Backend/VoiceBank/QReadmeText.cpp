#include "QReadmeText.h"

QTextCodec *QReadmeText::defaultCodec = nullptr;

QReadmeText::QReadmeText(QObject *parent) : PlainTextFile(parent) {
    m_codec = defaultCodec;
}

QReadmeText::QReadmeText(const QString &filename, QObject *parent)
    : PlainTextFile(filename, parent) {
    m_codec = defaultCodec;
}

QReadmeText::~QReadmeText() {
}

QTextCodec *QReadmeText::codeForDefault() {
    return defaultCodec;
}

void QReadmeText::setCodeForDefault(QTextCodec *codec) {
    defaultCodec = codec;
}
