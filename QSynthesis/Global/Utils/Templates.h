#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <QList>

template <class T>
void insertSort(QList<T> array) {
    int i, j;
    T key;

    for (j = 1; j < array.size(); ++j) {
        key = array[j];
        i = j - 1;
        while (i >= 0 && key < array[i]) {
            array[i + 1] = array[i];
            i = i - 1;
        }
        array[i + 1] = key;
    }
}

template <class T>
void insertSort(QVector<T> array) {
    int i, j;
    T key;

    for (j = 1; j < array.size(); ++j) {
        key = array[j];
        i = j - 1;
        while (i >= 0 && key < array[i]) {
            array[i + 1] = array[i];
            i = i - 1;
        }
        array[i + 1] = key;
    }
}

template <class T>
QList<T> batchReplace(const QList<T> &list, T fun(const T &)) {
    QList<T> res;
    for (auto it = list.begin(); it != list.end(); ++it) {
        res.append(fun(*it));
    }
    return res;
}

#endif // TEMPLATES_H
