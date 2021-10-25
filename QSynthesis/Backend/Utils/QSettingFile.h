#ifndef QSETTINGFILE_H
#define QSETTINGFILE_H

/*
 * Copyright 2019-2020 by Sinestr.
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include <QMap>
#include <QTextCodec>

// Section
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

// File
class QSettingFile {
public:
    explicit QSettingFile();
    virtual ~QSettingFile();

    bool load(const QString &filename);
    bool save(const QString &filename);

    void fromLines(const QStringList &list);
    QStringList toLines() const;

    typedef QSettingSection Section;

public:
    Section *sectionOf(const QString &name);
    QList<Section> sections() const;

    bool contains(const QString &name) const;
    bool isEmpty() const;

    bool addPairsSection(const QString &name, const QList<QPair<QString, QString>> &pairs);
    bool addArraySection(const QString &name, const QString &prefix, const QStringList &values,
                         int begin = 1);
    void addSection(const Section &section);

    bool removeSection(const QString &name);

    void clear();

    QTextCodec *codec() const;
    void setCodec(QTextCodec *codec);

    bool breakAfterSection() const;
    void setBreakAfterSection(bool breakAfterSection);

private:
    QList<QString> names;
    QMap<QString, Section> map;

private:
    QTextCodec *m_codec;
    bool m_breakAfterSection;

    bool parseSectionName(const QString &oName, QString &oResult);

public:
    static const QString SECTION_BEGIN_MARK;
    static const QString SECTION_END_MARK;
};

#endif // QSETTINGFILE_H
