#include "QNoteEnvelope.h"

QNoteEnvelope::QNoteEnvelope() {
    m_strEnvelope = "";
}

QVector<QControlPoint> QNoteEnvelope::getEnvelope() const {
    QVector<QControlPoint> aEnvelopeVector;
    aEnvelopeVector = StringToEnvelope(m_strEnvelope);

    for (QVector<QControlPoint>::size_type i = 0; i < aEnvelopeVector.size(); i++) {
        if (aEnvelopeVector[i].mX == NODEF_DOUBLE) {
            aEnvelopeVector[i].mX = 0.0;
        }
        if (aEnvelopeVector[i].mY == NODEF_DOUBLE) {
            aEnvelopeVector[i].mY = 0.0;
        }
    }
    return aEnvelopeVector;
}

void QNoteEnvelope::setEnvelope(const QVector<QControlPoint> &oCorrectedEnvelope) {
    m_strEnvelope = EnvelopeToString(oCorrectedEnvelope);
}

QVector<QControlPoint> QNoteEnvelope::StringToEnvelope(const QString &oStr) {
    QVector<QString> aVectorString = qstring_to_qvector_qstring(oStr);
    QVector<double> aVectorDouble;
    QVector<QControlPoint> aEnvelope;

    if (aVectorString.size() >= 8) {
        aVectorString.erase(aVectorString.begin() + 7);
    } else if (aVectorString.size() < 7) {
        return {};
    }

    aVectorDouble = qvector_qstring_to_qvector_double(aVectorString);
    if (aVectorDouble.size() % 2 != 0) {
        aVectorDouble.push_back(NODEF_DOUBLE);
    }

    aEnvelope.push_back(QControlPoint(aVectorDouble[0], aVectorDouble[3]));
    aEnvelope.push_back(QControlPoint(aVectorDouble[1], aVectorDouble[4]));
    if (aVectorDouble.size() == NUM_ENVELOPE_POINTS * 2) {
        aEnvelope.push_back(QControlPoint(aVectorDouble[8], aVectorDouble[9]));
    }
    aEnvelope.push_back(QControlPoint(aVectorDouble[2], aVectorDouble[5]));
    aEnvelope.push_back(QControlPoint(aVectorDouble[7], aVectorDouble[6]));
    return aEnvelope;
}

QString QNoteEnvelope::EnvelopeToString(const QVector<QControlPoint> &oEnvelope) {
    int aOffset;
    QVector<QString> aVectorString;
    QVector<double> aVectorDouble;

    if (oEnvelope.size() < 4) {
        return "";
    }

    aOffset = (oEnvelope.size() == NUM_ENVELOPE_POINTS);
    aVectorDouble.push_back(oEnvelope[0].mX);
    aVectorDouble.push_back(oEnvelope[1].mX);
    aVectorDouble.push_back(oEnvelope[2 + aOffset].mX);
    aVectorDouble.push_back(oEnvelope[0].mY);
    aVectorDouble.push_back(oEnvelope[1].mY);
    aVectorDouble.push_back(oEnvelope[2 + aOffset].mY);
    aVectorDouble.push_back(oEnvelope[3 + aOffset].mY);
    aVectorDouble.push_back(oEnvelope[3 + aOffset].mX);
    if (oEnvelope.size() == NUM_ENVELOPE_POINTS) {
        aVectorDouble.push_back(oEnvelope[2].mX);
        aVectorDouble.push_back(oEnvelope[2].mY);
    }

    if (aVectorDouble.size() == 8 && aVectorDouble[7] == 0.0) {
        aVectorDouble.pop_back();
    }
    aVectorString = qvector_double_to_qvector_qstring(aVectorDouble);

    if (aVectorString.size() > 7) {
        aVectorString.insert(aVectorString.begin() + 7, "%");
    }
    return qvector_qstring_to_qstring(aVectorString);
}

void QNoteEnvelope::setStrEnvelope(const QString &value) {
    m_strEnvelope = value;
}

QString QNoteEnvelope::strEnvelope() const {
    return m_strEnvelope;
}
