#ifndef OTOOPERATION_H
#define OTOOPERATION_H

#include "QOtoSample.h"
#include "VoiceOperation.h"

class OtoOperation : public VoiceOperation {
public:
    enum Type { Unknown, Change, Add, Remove, Move };

public:
    OtoOperation();
    virtual ~OtoOperation();

    int index() const;
    void setIndex(int index);

    QString dirname() const;
    void setDirname(const QString &dirname);

    Type type() const;

protected:
    Type m_typeO;

private:
    int m_index;
    QString m_dirname;
};

#endif // OTOOPERATION_H
