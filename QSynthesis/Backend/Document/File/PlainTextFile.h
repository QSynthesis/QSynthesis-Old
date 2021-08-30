#ifndef PLAINTEXTFILE_H
#define PLAINTEXTFILE_H

#include "NormalFile.h"

class PlainTextFile : public NormalFile {
    Q_OBJECT
public:
    explicit PlainTextFile(QObject *parent = nullptr);
    explicit PlainTextFile(const QString &filename, QObject *parent = nullptr);
    virtual ~PlainTextFile();

    void setData(const QByteArray &data) = delete;
    QByteArray data() const = delete;

    QTextCodec *codec() const;
    void setCodec(QTextCodec *codec);

    QString text() const;
    void setText(const QString &text);

protected:
    QTextCodec *m_codec;
    QString m_text;

private:
    bool loadCore(bool *valid = nullptr) override;
    bool saveCore() override;

    void resetCore() override;
};

#endif // PLAINTEXTFILE_H
