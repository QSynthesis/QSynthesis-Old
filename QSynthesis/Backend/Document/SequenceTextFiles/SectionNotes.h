#ifndef SECTIONNOTES_H
#define SECTIONNOTES_H

#include <QVector>

#include "Note/QLinkNote.h"

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
#endif // SECTIONNOTES_H
