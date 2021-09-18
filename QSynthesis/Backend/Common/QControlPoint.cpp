#include "QControlPoint.h"
#include "QUtauConstants.h"

QControlPoint::QControlPoint() {
    mX = 0.0;
    mY = 0.0;
    mP = Qs::sJoin;
}

QControlPoint::QControlPoint(const QControlPoint &oPoint) {
    mX = oPoint.mX;
    mY = oPoint.mY;
    mP = oPoint.mP;
}

QControlPoint::QControlPoint(double oX, double oY) {
    mX = oX;
    mY = oY;
    mP = Qs::sJoin;
}

QControlPoint::QControlPoint(double oX, double oY, Qs::PitchPoint oP) {
    mX = oX;
    mY = oY;
    mP = oP;
}

QControlPoint &QControlPoint::operator=(const QControlPoint &oPoint) {
    mX = oPoint.mX;
    mY = oPoint.mY;
    mP = oPoint.mP;

    return *this;
}

QControlPoint QControlPoint::operator+(const QControlPoint &oPoint) const {
    QControlPoint aResult;
    aResult.mX = mX + oPoint.mX;
    aResult.mY = mY + oPoint.mY;

    return aResult;
}

QControlPoint &QControlPoint::operator+=(const QControlPoint &oPoint) {
    mX += oPoint.mX;
    mY += oPoint.mY;

    return *this;
}

QControlPoint QControlPoint::operator-() const {
    QControlPoint aResult(-mX, -mY, mP);
    return aResult;
}

QControlPoint QControlPoint::operator-(const QControlPoint &oPoint) const {
    QControlPoint aResult;
    aResult.mX = mX - oPoint.mX;
    aResult.mY = mY - oPoint.mY;

    return aResult;
}

QControlPoint &QControlPoint::operator-=(const QControlPoint &oPoint) {
    mX -= oPoint.mX;
    mY -= oPoint.mY;

    return *this;
}

bool QControlPoint::operator==(const QControlPoint &oPoint) const {
    return (oPoint.mX == mX && oPoint.mY == mY && oPoint.mP == mP);
}

bool QControlPoint::operator!=(const QControlPoint &oPoint) const {
    return !((*this) == oPoint);
}

bool QControlPoint::operator<(const QControlPoint &oPoint) const {
    return mX < oPoint.mX;
}

QDebug operator<<(QDebug debug, const QControlPoint &oPoint) {
    QString info =
        QString("QControlPoint(mX:%1; mY:%2; mP:%3)").arg(oPoint.mX).arg(oPoint.mY).arg(oPoint.mP);
    debug.noquote() << info;
    return debug;
}

void pointListSort(QList<QControlPoint> &array) {
    int i, j;
    QControlPoint key;

    for (j = 1; j < array.size(); ++j) {
        key = array[j];
        i = j - 1;
        while (i >= 0 && array[i].mX > key.mX) {
            array[i + 1] = array[i];
            i = i - 1;
        }
        array[i + 1] = key;
    }
}
