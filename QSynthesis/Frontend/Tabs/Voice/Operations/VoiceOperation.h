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

protected:
    Type m_type;
};

#endif // VOICEOPERATION_H
