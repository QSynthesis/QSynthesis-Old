#ifndef SEQUENCETEXTDATA_H
#define SEQUENCETEXTDATA_H

#include "Note/QLinkNote.h"
#include "QUtauStrings.h"

struct SectionSettings {
public:
    SectionSettings();
    void clear();

    double globalTempo;
    QString globalFlags;

    QString projectName;
    QString outputFileName;

    QString voiceDirectory;
    QString cacheDirectory;

    QString wavtoolPath;
    QString resamplerPath;

    bool isMode2;

    bool operator==(const SectionSettings &another) const;
    bool operator!=(const SectionSettings &another) const;
};

// Project File Version
class SectionVersion {
public:
    SectionVersion();
    void clear();

    QString version;
    QString charset;

    bool operator==(const SectionVersion &another) const;
    bool operator!=(const SectionVersion &another) const;
};

// Project File Notes
class SectionNotes : public QVector<QLinkNote> {
public:
    SectionNotes();
    SectionNotes(QVector<QLinkNote> &&notes);

    double initTempo() const;
    void setInitTempo(double initTempo);

    QString trackName() const;
    void setTrackName(const QString &trackName);

    void setData(QVector<QLinkNote> &&notes);
    void setData(const QVector<QLinkNote> &notes);

private:
    double m_initTempo;
    QString m_trackName;
};

#endif // SEQUENCETEXTDATA_H
