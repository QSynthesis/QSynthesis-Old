#include "QGenonSettings.h"
#include "QUtils.h"

QGenonSettings::QGenonSettings() {
    clear();
}

QGenonSettings::QGenonSettings(const QString &filename) {
    clear();
    mFileName = filename;
}

bool QGenonSettings::operator<(const QGenonSettings &oGenon) const {
    return mFileName.toLower() < oGenon.mFileName.toLower();
}

bool QGenonSettings::operator==(const QGenonSettings &oGenon) const {
    return (mFileName == oGenon.mFileName) && (mAlias == oGenon.mAlias) &&
           (mOffset == oGenon.mOffset) && (mConstant == oGenon.mConstant) &&
           (mBlank == oGenon.mBlank) && (mPreUtterance == oGenon.mPreUtterance) &&
           (mVoiceOverlap == oGenon.mVoiceOverlap);
}

bool QGenonSettings::operator!=(const QGenonSettings &oGenon) const {
    return !((*this) == oGenon);
}

void QGenonSettings::clear() {
    mFileName = "";
    mAlias = "";
    mOffset = 0.0;
    mConstant = 0.0;
    mBlank = 0.0;
    mPreUtterance = 0.0;
    mVoiceOverlap = 0.0;
}

QDebug operator<<(QDebug debug, const QGenonSettings &oGenon) {
    QString info =
        QString("QGenonSettings(file:\"%1\"; alias:\"%2\";)").arg(oGenon.mFileName, oGenon.mAlias);
    debug.noquote() << info;
    return debug;
}

bool QGenonSettings::isEmpty() const {
    return (mAlias.isEmpty() && (mOffset == 0.0) && (mOffset == 0.0) && (mConstant == 0.0) &&
            (mBlank == 0.0) && (mPreUtterance == 0.0) && (mVoiceOverlap == 0.0));
}

bool QGenonSettings::valid() const {
    return isFileExist(mFileName);
}

QString QGenonSettings::frqFile() const {
    QFileInfo info(mFileName);
    return info.absolutePath() + Slash + info.baseName() + "_wav.frq";
}

bool QGenonSettings::frqExist() const {
    return isFileExist(frqFile());
}

QCorrectGenon::QCorrectGenon() {
    PreUtterance = VoiceOverlap = StartPoint = 0;
}

QCorrectGenon::QCorrectGenon(double pre, double ove, double stp) {
    PreUtterance = pre;
    VoiceOverlap = ove;
    StartPoint = stp;
}

bool QCorrectGenon::operator==(const QCorrectGenon &oCorrect) const {
    return (PreUtterance == oCorrect.PreUtterance) && (VoiceOverlap == oCorrect.VoiceOverlap) &&
           (StartPoint == oCorrect.StartPoint);
}

bool QCorrectGenon::operator!=(const QCorrectGenon &oCorrect) const {
    return !((*this) == oCorrect);
}

QDebug operator<<(QDebug debug, const QCorrectGenon &oCorrect) {
    QString info =
        QString("QCorrectGenon(pre:%1;ove:%2;stp:%3)")
            .arg(QString::number(oCorrect.PreUtterance), QString::number(oCorrect.VoiceOverlap),
                 QString::number(oCorrect.StartPoint));
    debug.noquote() << info;
    return debug;
}
