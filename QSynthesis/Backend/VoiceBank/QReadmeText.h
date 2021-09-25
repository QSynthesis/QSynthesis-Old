#ifndef QREADMETEXT_H
#define QREADMETEXT_H

#include "File/PlainTextFile.h"
#include "Macros.h"

class QReadmeText : public PlainTextFile {
    Q_OBJECT
    Q_CHARSET
public:
    explicit QReadmeText(QObject *parent = nullptr);
    explicit QReadmeText(const QString &filename, QObject *parent = nullptr);
    virtual ~QReadmeText();
};

#endif // QREADMETEXT_H
