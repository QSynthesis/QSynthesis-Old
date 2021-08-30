#ifndef QGenonSettings_H
#define QGenonSettings_H

#include <QDebug>

// Normal Oto Sample
struct QGenonSettings {
    QString mFileName;
    QString mAlias;
    double mOffset;
    double mConstant;
    double mBlank;
    double mPreUtterance;
    double mVoiceOverlap;

    QGenonSettings();
    QGenonSettings(const QString &filename);

    bool operator<(const QGenonSettings &oGenon) const;
    bool operator==(const QGenonSettings &oGenon) const;
    bool operator!=(const QGenonSettings &oGenon) const;

    friend QDebug operator<<(QDebug debug, const QGenonSettings &oGenon);

    void clear();
    bool isEmpty() const;

    bool valid() const;

    QString frqFile() const;
    bool frqExist() const;
};

// Fixed Sample Variables
struct QCorrectGenon {
    double PreUtterance;
    double VoiceOverlap;
    double StartPoint;

    explicit QCorrectGenon();
    explicit QCorrectGenon(double pre, double ove, double stp);

    bool operator==(const QCorrectGenon &oCorrect) const;
    bool operator!=(const QCorrectGenon &oCorrect) const;

    friend QDebug operator<<(QDebug debug, const QCorrectGenon &oCorrect);
};

#endif // QGenonSettings_H
