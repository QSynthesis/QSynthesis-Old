#ifndef NOTEOPERATION_H
#define NOTEOPERATION_H

#include "TuneOperation.h"

class NoteOperation : public TuneOperation {
public:
    enum Type {
        Unknown,
        Move,
        Length,
        Add,
        Remove,
        Mode2,
        Envelope,
        Vibrato,
        Mode1,
        Lyrics,
        Intensity,
        Modulation,
        PreUtterance,
        VoiceOverlap,
        StartPoint,
        Flags,
        Velocity,
        Tempo,
    };

    NoteOperation();
    virtual ~NoteOperation();

    QList<int> index() const;
    void setIndex(const QList<int> &index);

    Type type() const;

    NoteOperation *next() const;

protected:
    QList<int> m_index;
    Type m_typeN;
};

#endif // NOTEOPERATION_H
