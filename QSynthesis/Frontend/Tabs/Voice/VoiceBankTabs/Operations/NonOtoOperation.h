#ifndef NONOTOOPERATION_H
#define NONOTOOPERATION_H

#include "VoiceOperation.h"

class NonOtoOperation : public VoiceOperation {
public:
    enum Type { Unknown, PrefixMap, InfoText };

public:
    NonOtoOperation();
    virtual ~NonOtoOperation();

    Type type() const;

protected:
    Type m_typeN;
};

#endif // NONOTOOPERATION_H
