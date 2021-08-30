#include "QNoteMode2.h"
#include "QUtauConstants.h"
#include "QUtauUtils.h"

QNoteMode2::QNoteMode2() {
    strPBS = strPBW = strPBY = strPBM = "";
}

void QNoteMode2::SetStrings(const QString &oPBS, const QString &oPBW, const QString &oPBY,
                            const QString &oPBM) {
    strPBS = oPBS;
    strPBW = oPBW;
    strPBY = oPBY;
    strPBM = oPBM;
}

void QNoteMode2::ExportStrings(QString &oPBS, QString &oPBW, QString &oPBY, QString &oPBM) {
    oPBS = strPBS;
    oPBW = strPBW;
    oPBY = strPBY;
    oPBM = strPBM;
}

void QNoteMode2::SetPBS(const QString &oPBS) {
    strPBS = oPBS;
}

void QNoteMode2::SetPBW(const QString &oPBW) {
    strPBW = oPBW;
}

void QNoteMode2::SetPBY(const QString &oPBY) {
    strPBY = oPBY;
}

void QNoteMode2::SetPBM(const QString &oPBM) {
    strPBM = oPBM;
}

QVector<QControlPoint> QNoteMode2::GetCorrectedPortamento() const {
    QVector<double> aPBSXY, aPBWs, aPBYs;
    QVector<QString> aPBMs;
    QControlPoint aPoint;
    QVector<QControlPoint> oCorrectedPitch;

    if (strPBS.isEmpty() || strPBW.isEmpty()) {
        return {};
    }

    oCorrectedPitch.clear();
    aPBSXY = qstring_to_qvector_double(strPBS, ";");

    if (!aPBSXY.isEmpty()) {
        aPoint.mX = aPBSXY[0];
        if (aPBSXY.size() >= 2) {
            aPoint.mY = aPBSXY[1];
        } else {
            aPoint.mY = 0;
        }
    }

    oCorrectedPitch.push_back(aPoint);

    aPBWs = qstring_to_qvector_double(strPBW);
    aPBYs = qstring_to_qvector_double(strPBY);
    aPBMs = qstring_to_qvector_qstring(strPBM);

    for (int i = 0; i < qMax(aPBWs.size(), aPBYs.size()); i++) {
        aPoint = QControlPoint();
        if (aPBWs.size() > i) {
            aPoint.mX = aPBWs[i];
        }
        if (aPBYs.size() > i) {
            aPoint.mY = (aPBYs[i] == NODEF_DOUBLE) ? 0 : aPBYs[i];
        }
        if (aPBMs.size() > i) {
            aPoint.mP = (aPBMs[i] == NODEF_STRING) ? Qs::sType : Qs::stringToPitchPoint(aPBMs[i]);
        }
        aPoint.mX += oCorrectedPitch.back().mX;
        oCorrectedPitch.push_back(aPoint);
    }

    // Negative Correction
    for (int i = 1; i < oCorrectedPitch.size(); ++i) {
        QControlPoint &curPoint = oCorrectedPitch[i];
        QControlPoint &prevPoint = oCorrectedPitch[i - 1];

        if (curPoint.mX < prevPoint.mX) {
            curPoint.mX = prevPoint.mX;
        }
    }

    return oCorrectedPitch;
}

void QNoteMode2::SetCorrectedPortamento(const QVector<QControlPoint> &oCorrectedPitch) {
    QVector<double> aVectorDouble;
    QVector<QString> aVectorString;

    if (oCorrectedPitch.isEmpty()) {
        return;
    }

    aVectorDouble.clear();
    aVectorDouble.push_back(oCorrectedPitch[0].mX);

    if (oCorrectedPitch[0].mY != 0) {
        aVectorDouble.push_back(oCorrectedPitch[0].mY);
    }
    strPBS = qvector_double_to_qstring(aVectorDouble, ";");

    aVectorDouble.clear();
    for (QVector<QControlPoint>::size_type i = 1; i < oCorrectedPitch.size(); i++) {
        aVectorDouble.push_back(oCorrectedPitch[i].mX - oCorrectedPitch[i - 1].mX);
    }
    strPBW = qvector_double_to_qstring(aVectorDouble);

    aVectorDouble.clear();
    for (QVector<QControlPoint>::size_type i = 1; i < oCorrectedPitch.size(); i++) {
        aVectorDouble.push_back(oCorrectedPitch[i].mY);
    }
    strPBY = qvector_double_to_qstring(aVectorDouble);

    aVectorString.clear();
    for (QVector<QControlPoint>::size_type i = 1; i < oCorrectedPitch.size(); i++) {
        aVectorString.push_back(Qs::pitchPointToString(oCorrectedPitch[i].mP));
    }

    strPBM = qvector_qstring_to_qstring(aVectorString);
}
