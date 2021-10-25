#include "Primary.h"

QString removeTailSlashes(const QString &dirname) {
    QString path = dirname;
    while (!path.isEmpty() && (path.endsWith('/') || path.endsWith('\\'))) {
        path = path.mid(0, path.size() - 1);
    }
    return path;
}

QList<int> toIntList(const QStringList &list) {
    QList<int> res;
    for (auto it = list.begin(); it != list.end(); ++it) {
        bool isNum;
        int num = it->toInt(&isNum);
        if (!isNum) {
            return {};
        }
        res.append(num);
    }
    return res;
}

QList<double> toDoubleList(const QStringList &list) {
    QList<double> res;
    for (auto it = list.begin(); it != list.end(); ++it) {
        bool isNum;
        int num = it->toDouble(&isNum);
        if (!isNum) {
            return {};
        }
        res.append(num);
    }
    return res;
}
