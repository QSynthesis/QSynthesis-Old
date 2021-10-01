#ifndef QGenonSettings_H
#define QGenonSettings_H

#include <QDebug>

// Normal Oto Sample
struct QGenonSettings {
    QString mFileName;
    QString mAlias;
    double mOffset;
    double mConstant; // Also signed as Consonant
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

    QString frqFile() const; // Resampler Frequency Map File
    bool frqExist() const;

    QString mrqFile() const; // Moresampler Frequency Map File
    bool mrqExist() const;

    static QString fromFrqFileName(const QString &filename);
    static QString toFrqFileName(const QString &filename);
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
