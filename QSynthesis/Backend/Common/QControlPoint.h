#ifndef QCONTROLPOINT_H
#define QCONTROLPOINT_H

#include <QDebug>

#include "Types.h"

struct QControlPoint {
public:
    QControlPoint();
    QControlPoint(const QControlPoint &oPoint);

    QControlPoint(double oX, double oY);
    QControlPoint(double oX, double oY, Qs::PitchPoint oP);

    QControlPoint &operator=(const QControlPoint &oPoint);

    QControlPoint operator+(const QControlPoint &oPoint) const;
    QControlPoint &operator+=(const QControlPoint &oPoint);

    QControlPoint operator-() const;

    QControlPoint operator-(const QControlPoint &oPoint) const;
    QControlPoint &operator-=(const QControlPoint &oPoint);

    bool operator==(const QControlPoint &oPoint) const;
    bool operator!=(const QControlPoint &oPoint) const;
    bool operator<(const QControlPoint &oPoint) const;

    friend QDebug operator<<(QDebug debug, const QControlPoint &oPoint);

    double mX;
    double mY;
    Qs::PitchPoint mP;
};

void pointListSort(QList<QControlPoint> &array);

#endif // QCONTROLPOINT_H
