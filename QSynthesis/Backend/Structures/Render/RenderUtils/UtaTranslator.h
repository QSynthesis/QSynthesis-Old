#ifndef UTATRANSLATOR_H
#define UTATRANSLATOR_H

#include "QControlPoint.h"
#include "QUtils.h"

namespace UtaTranslator {

    QString loadingBar(int n, int sum);

    QString convertEnvelope(const QString &s, const double &overlap);

    QStringList convertEnvelopeFromVector(const QVector<QControlPoint> &tpoints,
                                          const double &overlap);

    QString fixFlags(const QString &s);

    void getCorrectPBSY(int prevNoteNum, const QString &prevLyric, int curNoteNum,
                        QControlPoint &curPoint);

    QVector<QControlPoint> defaultPitch(const int &prevNoteNum, const QString &prevLyric,
                                        const int &curNoteNum);

    QString compatibleFileName(const QString &filename);

}; // namespace UtaTranslator

#endif // UTATRANSLATOR_H
