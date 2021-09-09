#include "QSettingSection.h"

const QString QSettingSection::KEY_VALUE_SEPARATOR = "=";

QSettingSection::QSettingSection() {
}

QSettingSection::QSettingSection(const QString &name) {
    setSectionName(name);
}

QSettingSection::~QSettingSection() {
}

void QSettingSection::fromLines(const QStringList &list) {
    QString line;
    int eq;

    QString key, value;
    auto it = list.begin();
    while (it != list.end()) {
        line = *it;
        ++it;

        if (line.isEmpty()) {
            continue;
        }
        eq = line.indexOf(QSettingSection::KEY_VALUE_SEPARATOR);
        if (eq > 0) {
            key = line.left(eq);
            value = line.mid(eq + 1);
            addPair(key, value);
        } else {
            unformatted.append(line);
        }
    }
}

QStringList QSettingSection::toLines() const {
    QStringList list;
    const QList<QPair<QString, QString>> &pairs = toPairList();
    QString line;
    for (int i = 0; i < pairs.size(); ++i) {
        QPair<QString, QString> pair = pairs.at(i);
        line = pair.first + QSettingSection::KEY_VALUE_SEPARATOR + pair.second;
        list.append(line);
    }
    for (int i = 0; i < unformatted.size(); ++i) {
        list.append(unformatted.at(i));
    }
    return list;
}

QString QSettingSection::sectionName() const {
    return name;
}

void QSettingSection::setSectionName(const QString &name) {
    this->name = name;
}

bool QSettingSection::isArray(QString *prefix) const {
    if (map.isEmpty()) {
        return false;
    }

    QString curPrefix, lastPrefix;
    for (int i = 0; i < keys.size(); ++i) {
        curPrefix = keys.at(i);
        while (!curPrefix.isEmpty() && curPrefix.back().isDigit()) {
            curPrefix = curPrefix.mid(0, curPrefix.size() - 1);
        }

        if (i != 0 && curPrefix != lastPrefix) {
            return false;
        }
        lastPrefix = curPrefix;
    }
    if (prefix) {
        *prefix = curPrefix;
    }

    return true;
}

QStringList QSettingSection::toArray() const {
    QStringList list;
    for (int i = 0; i < keys.size(); ++i) {
        list.append(map[keys.at(i)]);
    }
    return list;
}

QList<QPair<QString, QString>> QSettingSection::toPairList() const {
    QList<QPair<QString, QString>> list;
    for (int i = 0; i < keys.size(); ++i) {
        QString key = keys.at(i);
        list.append(qMakePair(key, map[key]));
    }
    return list;
}

QString *QSettingSection::valueOf(const QString &key) {
    auto it = map.find(key);
    if (it == map.end()) {
        return nullptr;
    }
    return &it.value();
}

bool QSettingSection::containsKey(const QString &key) {
    return map.contains(key);
}

bool QSettingSection::isEmpty() const {
    return keys.isEmpty();
}

bool QSettingSection::addPair(const QString &key, const QString &value) {
    if (map.contains(key)) {
        return false;
    }
    map.insert(key, value);
    keys.append(key);
    return true;
}

bool QSettingSection::removePair(const QString &key) {
    auto it = map.find(key);
    if (it == map.end()) {
        return false;
    }
    map.erase(it);
    keys.removeOne(key);
    return true;
}

void QSettingSection::clear() {
    map.clear();
    keys.clear();
}

void QSettingSection::clearAll() {
    name.clear();
    clear();
    clearUnformattedLines();
}

QStringList QSettingSection::unformattedLines() const {
    return unformatted;
}

void QSettingSection::setUnformattedLines(const QStringList &unformatted) {
    this->unformatted = unformatted;
}

void QSettingSection::clearUnformattedLines() {
    unformatted.clear();
}
