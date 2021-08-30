#include "CharsetHandler.h"

CharsetHandler::CharsetHandler() {
}

CharsetHandler::CharsetHandler(QString filename) {
    setFilename(filename);
}

QString CharsetHandler::filename() const {
    return m_filename;
}

void CharsetHandler::setFilename(const QString &filename) {
    m_filename = filename;

    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    file.close();

    QByteArray data = file.readAll();
    m_charset = detectCharset(data);
}

QString CharsetHandler::charset() const {
    return m_charset;
}

QString CharsetHandler::detectCharset(const QByteArray &data) {
    QTextCodec *autoCodec = QTextCodec::codecForUtfText(data);
    QString name = autoCodec->name();
    QString charset;

    if (name == "ISO-8859-1") {
        charset = "";
    } else {
        charset = name;
        return charset;
    }

    QList<QTextCodec *> codecs{QTextCodec::codecForName("UTF-8")};

    for (auto it = codecs.begin(); it != codecs.end(); ++it) {
        QTextCodec::ConverterState state;
        QTextCodec *codec = *it;
        QString text = codec->toUnicode(data.constData(), data.size(), &state);

        if (state.invalidChars == 0) {
            charset = codec->name();
            break;
        }
    }
    return charset;
}
