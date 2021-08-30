#ifndef QOTOSAMPLELIST_H
#define QOTOSAMPLELIST_H

#include "QOtoSample.h"

class QOtoSampleList : public QList<QOtoSample> {
public:
    QOtoSampleList();

    int insertAuto(const QOtoSample &sample, bool replace = false);
    int insertAuto(const QGenonSettings &genon, bool replace = false);

    bool containsAuto(const QOtoSample &sample);
    int findAuto(const QOtoSample &sample, int *pos = nullptr);

private:
    int binarySearch(const QOtoSample &sample);
};

#endif // QOTOSAMPLELIST_H
