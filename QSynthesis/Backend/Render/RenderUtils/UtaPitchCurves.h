#ifndef UTAPITCHCURVES_H
#define UTAPITCHCURVES_H

#include "Common/QControlPoint.h"

#define PI 3.1415926

extern const char Base64EncodeMap[];

namespace UtaPitchCurves {

    double f_x(const double &x1, const double &y1, const double &x2, const double &y2,
               const double &x);

    double f_r(const double &x1, const double &y1, const double &x2, const double &y2,
               const double &x);

    double f_j(const double &x1, const double &y1, const double &x2, const double &y2,
               const double &x);

    double f_s(const double &x1, const double &y1, const double &x2, const double &y2,
               const double &x);

    double f_type(const Qs::PitchPoint &ptype, const double &x1, const double &y1,
                  const double &x2, const double &y2, const double &x);

    QVector<int> convert_from_vector_point(
        const double &tempo1, const QVector<QControlPoint> &curNote, const QVector<double> &curVBR,
        const double &curPre, const double &curStp, const int &curLength,

        const QVector<QControlPoint> &nextNote = {}, const QVector<double> &nextVBR = {},
        const double &nextPre = 0, const double &nextOve = 0, const int &nextLength = 0,

        const QVector<QControlPoint> &prevNote = {}, const QVector<double> &prevVBR = {},
        const int &prevLength = 0);

    QString encode_from_vector(const QVector<int> &pitchBend);

    QString encode_single_num(int n);

    int find_impact(const QVector<QControlPoint> &portamento,
                    QVector<QControlPoint>::size_type &startIndex, int curTick,
                    const double &PositiveTempo, double NegativeTempo = 0,
                    const QVector<double> &vibrato = {}, const int &length = 0);

}; // namespace UtaPitchCurves

#endif // UTAPITCHCURVES_H
