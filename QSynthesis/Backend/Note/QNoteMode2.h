#ifndef QNOTEMODE2_H
#define QNOTEMODE2_H

#include "QControlPoint.h"

class QNoteMode2 {
public:
    QNoteMode2();

    void SetStrings(const QString &oPBS, const QString &oPBW, const QString &oPBY,
                    const QString &oPBM);
    void ExportStrings(QString &oPBS, QString &oPBW, QString &oPBY, QString &oPBM);

    void SetPBS(const QString &oPBS);
    void SetPBW(const QString &oPBW);
    void SetPBY(const QString &oPBY);
    void SetPBM(const QString &oPBM);

    QVector<QControlPoint> GetCorrectedPortamento() const;
    void SetCorrectedPortamento(const QVector<QControlPoint> &oCorrectedPitch);

private:
    QVector<double> PBS, PBW, PBY;
    QStringList PBM;

    QString strPBS, strPBW, strPBY, strPBM;
};

#endif // QNOTEMODE2_H
