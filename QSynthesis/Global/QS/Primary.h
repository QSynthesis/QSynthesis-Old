#ifndef PRIMARY_H
#define PRIMARY_H

#include <QList>
#include <QString>

#define _FIN(T) removeTailSlashes(QDir::fromNativeSeparators(T))
#define _FOUT(T) removeTailSlashes(QDir::toNativeSeparators(T))

QString removeTailSlashes(const QString &dirname);

QList<int> toIntList(const QStringList &list);

QList<double> toDoubleList(const QStringList &list);

// Template Functions
template <class T>
inline void insertSort(const QList<T> &array) {
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
inline void insertSort(const QVector<T> &array) {
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
inline QList<T> batchReplace(const QList<T> &list, T fun(const T &)) {
    QList<T> res;
    for (auto it = list.begin(); it != list.end(); ++it) {
        res.append(fun(*it));
    }
    return res;
}

#endif // PRIMARY_H
