#include "QReadmeText.h"

Q_CHARSET_DECLARE(QReadmeText)

QReadmeText::QReadmeText(QObject *parent) : PlainTextFile(parent) {
    m_codec = defaultCodec;
}

QReadmeText::QReadmeText(const QString &filename, QObject *parent)
    : PlainTextFile(filename, parent) {
    m_codec = defaultCodec;
}

QReadmeText::~QReadmeText() {
}
