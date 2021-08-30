#ifndef QREADMETEXT_H
#define QREADMETEXT_H

#include "File/PlainTextFile.h"

class QReadmeText : public PlainTextFile {
    Q_OBJECT
public:
    explicit QReadmeText(QObject *parent = nullptr);
    explicit QReadmeText(const QString &filename, QObject *parent = nullptr);
    virtual ~QReadmeText();

private:
    static QTextCodec *defaultCodec;

public:
    static QTextCodec *codeForDefault();
    static void setCodeForDefault(QTextCodec *codec);
};

#endif // QREADMETEXT_H
