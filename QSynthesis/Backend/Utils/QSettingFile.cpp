#include "QSettingFile.h"

#include <QFile>
#include <QMap>
#include <QTextStream>

const QString QSettingFile::SECTION_BEGIN_MARK = "[";
const QString QSettingFile::SECTION_END_MARK = "]";

QSettingFile::QSettingFile() {
    m_codec = QTextCodec::codecForLocale();
    m_breakAfterSection = false;
}

QSettingFile::~QSettingFile() {
}

bool QSettingFile::load(const QString &filename) {
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    QStringList list;

    QTextStream in(&file);
    in.setCodec(m_codec);
    while (!in.atEnd()) {
        list.append(in.readLine());
    }

    file.close();

    fromLines(list);
    return true;
}

bool QSettingFile::save(const QString &filename) {
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QIODevice::Text)) {
        return 0;
    }

    QStringList list = toLines();

    QTextStream out(&file);
    out.setCodec(m_codec);
    for (auto it = list.begin(); it != list.end(); ++it) {
        out << *it << Qt::endl;
    }

    file.close();
    return true;
}

void QSettingFile::fromLines(const QStringList &list) {
    QString line;

    QString name;
    Section section;
    QStringList lines;

    bool toAdd = false;
    auto it = list.begin();
    while (it != list.end()) {
        line = *it;
        ++it;

        if (line.isEmpty() && it != list.end()) {
            continue;
        }

        if (parseSectionName(line, name)) {
            if (toAdd) {
                section.fromLines(lines);
                addSection(section);
                section.clearAll();
                lines.clear();
            }
            section.setSectionName(name);
            toAdd = true;
        } else {
            lines.append(line);
        }

        // At end
        if (it == list.end()) {
            if (toAdd) {
                section.fromLines(lines);
                addSection(section);
                section.clearAll();
                lines.clear();
            }
        }
    }
}

QStringList QSettingFile::toLines() const {
    QStringList list;
    QList<Section> sections = this->sections();

    for (int i = 0; i < sections.size(); ++i) {
        list.append(SECTION_BEGIN_MARK + sections.at(i).sectionName() + SECTION_END_MARK);
        list.append(sections.at(i).toLines());
        if (m_breakAfterSection) {
            list.append("");
        }
    }

    return list;
}

QSettingFile::Section *QSettingFile::sectionOf(const QString &name) {
    auto it = map.find(name);
    if (it == map.end()) {
        return nullptr;
    }
    return &it.value();
}

QList<QSettingFile::Section> QSettingFile::sections() const {
    QList<Section> list;
    for (int i = 0; i < names.size(); ++i) {
        list.append(map[names.at(i)]);
    }
    return list;
}

bool QSettingFile::contains(const QString &name) const {
    return map.contains(name);
}

bool QSettingFile::isEmpty() const {
    return names.isEmpty();
}

bool QSettingFile::addPairsSection(const QString &name,
                                   const QList<QPair<QString, QString>> &pairs) {
    if (contains(name)) {
        return false;
    }
    Section section(name);
    for (int i = 0; i < pairs.size(); ++i) {
        section.addPair(pairs.at(i).first, pairs.at(i).second);
    }
    addSection(section);
    return true;
}

bool QSettingFile::addArraySection(const QString &name, const QString &prefix,
                                   const QStringList &values, int begin) {
    if (contains(name)) {
        return false;
    }
    Section section(name);
    for (int i = 0; i < values.size(); ++i) {
        section.addPair(prefix + QString::number(begin + i), values.at(i));
    }
    addSection(section);
    return true;
}

void QSettingFile::addSection(const QSettingFile::Section &section) {
    map.insert(section.sectionName(), section);
    names.append(section.sectionName());
}

bool QSettingFile::removeSection(const QString &name) {
    auto it = map.find(name);
    if (it == map.end()) {
        return false;
    }

    map.erase(it);
    names.removeOne(name);
    return true;
}

void QSettingFile::clear() {
    map.clear();
    names.clear();
}

QTextCodec *QSettingFile::codec() const {
    return m_codec;
}

void QSettingFile::setCodec(QTextCodec *codec) {
    m_codec = codec;
}

bool QSettingFile::breakAfterSection() const {
    return m_breakAfterSection;
}

void QSettingFile::setBreakAfterSection(bool breakAfterSection) {
    m_breakAfterSection = breakAfterSection;
}

bool QSettingFile::parseSectionName(const QString &oName, QString &oResult) {
    if (oName.startsWith(SECTION_BEGIN_MARK) && oName.endsWith(SECTION_END_MARK)) {
        oResult = oName.mid(SECTION_BEGIN_MARK.size(),
                            oName.size() - SECTION_BEGIN_MARK.size() - SECTION_END_MARK.size());
        return true;
    } else {
        return false;
    }
}
