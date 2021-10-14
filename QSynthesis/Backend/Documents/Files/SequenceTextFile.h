#ifndef SEQUENCETEXTFILE_H
#define SEQUENCETEXTFILE_H

#include "BaseFile.h"
#include "Macros.h"
#include "SequenceTextFiles/SequenceTextData.h"

#include <QFile>
#include <QTextCodec>

class SequenceTextFile : public BaseFile {
    Q_CHARSET
public:
    SequenceTextFile();
    SequenceTextFile(const QString &filename);
    ~SequenceTextFile();

protected:
    SequenceTextFile(Qs::VariableSource source); // Use by child class

public:
    SectionVersion sectionVersion() const;
    SectionVersion &sectionVersion();
    void setSectionVersion(const SectionVersion &value);

    SectionSettings sectionSettings() const;
    SectionSettings &sectionSettings();
    void setSectionSettings(const SectionSettings &value);

    QVector<QLinkNote> sectionNotes() const;
    QVector<QLinkNote> &sectionNotes();
    void setSectionNotes(const QVector<QLinkNote> &value);

    void clearSectionNotes();
    void appendSectionNote(const QLinkNote &oNote);
    QLinkNote popSectionNote();

private:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;

    // Version
    SectionVersion m_sectionVersion;

    // Settings
    SectionSettings m_sectionSettings;

    // Notes
    QVector<QLinkNote> m_sectionNotes;

    bool parseSectionName(const QString &name, QString &result);
    bool parseSectionNote(const QStringList &sectionList, QLinkNote &note);
    bool parseSectionVersion(const QStringList &sectionList, SectionVersion &version);
    bool parseSectionSettings(const QStringList &sectionList, SectionSettings &setting);

    void writeSectionName(const int &name, QTextStream &out);
    void writeSectionName(const QString &name, QTextStream &out);

    void writeSectionNote(int num, const QLinkNote &note, QTextStream &out);
    void writeSectionVersion(QTextStream &out);
    void writeSectionSettings(QTextStream &out);
};

#endif // SEQUENCETEXTFILE_H
