#include "QOtoSampleList.h"

QOtoSampleList::QOtoSampleList() {
}

int QOtoSampleList::insertAuto(const QOtoSample &sample, bool replace) {
    int index = binarySearch(sample);
    if (index < 0 || index >= size() || at(index) != sample) {
        insert(index, sample);
    } else {
        QOtoSample &sample2 = (*this)[index];
        if (replace) {
            sample2.setData(sample);
        } else {
            sample2.append(sample);
        }
    }
    return index;
}

int QOtoSampleList::insertAuto(const QGenonSettings &genon, bool replace) {
    QOtoSample sample;
    sample.setFilename(genon.mFileName);
    sample.append(genon);
    return insertAuto(sample, replace);
}

bool QOtoSampleList::containsAuto(const QOtoSample &sample) {
    return findAuto(sample) >= 0;
}

int QOtoSampleList::findAuto(const QOtoSample &sample, int *pos) {
    int index = binarySearch(sample);
    if (pos) {
        *pos = index;
    }
    if (index < 0 || index >= size() || at(index) != sample) {
        return -1;
    }
    return index;
}

int QOtoSampleList::binarySearch(const QOtoSample &sample) {
    int i, j, mid;
    i = 0;
    j = size() - 1;
    while (i <= j) {
        mid = i + (j - i) / 2;
        if (at(mid) < sample) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }
    return i;
}
