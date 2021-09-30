#ifndef QSETTINGSECTION_H
#define QSETTINGSECTION_H

#include <QMap>
#include <QString>

class QSettingSection {
public:
    QSettingSection();
    QSettingSection(const QString &name);
    ~QSettingSection();

    void fromLines(const QStringList &list);
    QStringList toLines() const;

public:
    QString sectionName() const;
    void setSectionName(const QString &name);

    bool isArray(QString *prefix = nullptr) const;

    QStringList toArray() const;
    QList<QPair<QString, QString>> toPairList() const;

    QString *valueOf(const QString &key);
    bool containsKey(const QString &key);

    bool isEmpty() const;

    bool addPair(const QString &key, const QString &value);
    bool addPair(const QString &key, int value);
    bool addPair(const QString &key, double value);
    bool removePair(const QString &key);

    void clear();
    void clearAll();

    QStringList unformattedLines() const;
    void setUnformattedLines(const QStringList &unformatted);
    void clearUnformattedLines();

private:
    QString name;
    QList<QString> keys;
    QMap<QString, QString> map;

    QStringList unformatted;

public:
    static const QString KEY_VALUE_SEPARATOR;
};

#endif // QSETTINGSECTION_H
