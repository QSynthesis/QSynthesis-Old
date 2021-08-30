#ifndef QLINKNOTE_H
#define QLINKNOTE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

#include "QControlPoint.h"
#include "QGenonSettings.h"
#include "QUtauConstants.h"
#include "QUtauStrings.h"

struct NoteProperties {
    NoteProperties();
    void clear();

    QString length;
    QString intensity;
    QString modulation;

    QString preUttr;
    QString overlap;

    QString tempo;

    QString flags;
    QString velocity;
    QString startpoint;

    QString preUttrOto;
    QString overlapOto;
};

class QLinkNote {
public:
    explicit QLinkNote();
    explicit QLinkNote(int noteNum, int length);
    explicit QLinkNote(int noteNum, int length, QString lrc);

public:
    QString lyric, flags;

    // int tick;
    int noteNum;
    int length;

    double intensity, modulation, preUttr, overlap, velocity, stp;
    double tempo;

    QList<double> vibrato;

    QList<QControlPoint> envelope;

    double pbstart;
    QList<double> pitches;
    QString pbtype;

    QString label, direct, patch, region, regionEnd;

    QList<QControlPoint> Mode2Pitch;
    QList<QPair<QString, QString>> customData;

public:
    void clear();
    void mode2Sort();
    void envSort();

    static QList<QControlPoint> defaultEnvelope();

    QJsonObject toJson() const;
    static QLinkNote fromJson(const QJsonObject &obj);

    friend QDebug operator<<(QDebug debug, const QLinkNote &oNote);

private:
    void resetValues();
};

#endif // QLINKNOTE_H
