#ifndef VOICEOPERATION_H
#define VOICEOPERATION_H

#include "Operation.h"

class VoiceOperation : public Operation {
public:
    enum Type { Unknown, NonOto, Oto };

public:
    VoiceOperation();
    virtual ~VoiceOperation();

    Type type() const;

    virtual bool differ() const;

    VoiceOperation *next() const;
    void setNext(VoiceOperation *next);

protected:
    Type m_type;
    VoiceOperation *m_next;
};

#endif // VOICEOPERATION_H
