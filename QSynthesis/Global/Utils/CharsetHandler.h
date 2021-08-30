#ifndef CHARSETHANDLER_H
#define CHARSETHANDLER_H

#include <QDebug>
#include <QFile>
#include <QTextCodec>

class CharsetHandler {
public:
    CharsetHandler();
    CharsetHandler(QString filename);

    QString filename() const;
    void setFilename(const QString &filename);

    QString charset() const;
    static QString detectCharset(const QByteArray &data);

private:
    QString m_filename;
    QString m_charset;
};

#endif // CHARSETHANDLER_H
