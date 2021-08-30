#ifndef QNOTEENVELOPE_H
#define QNOTEENVELOPE_H

#include "QControlPoint.h"
#include "QUtauConstants.h"
#include "QUtauUtils.h"

class QNoteEnvelope {
public:
    QNoteEnvelope();

    QVector<QControlPoint> getEnvelope() const;
    void setEnvelope(const QVector<QControlPoint> &oCorrectedEnvelope);

    void setStrEnvelope(const QString &value);
    QString strEnvelope() const;

private:
    QString m_strEnvelope;

    static QVector<QControlPoint> StringToEnvelope(const QString &oStr);
    static QString EnvelopeToString(const QVector<QControlPoint> &oEnvelope);
};

#endif // QNOTEENVELOPE_H
