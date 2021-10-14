#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "BaseFile.h"
#include "Macros.h"

class ConfigFile : public BaseFile {
public:
    ConfigFile();
    ConfigFile(const QString &filename);
    ~ConfigFile();

private:
    bool loadCore(bool *valid = nullptr) override;
    bool saveCore() override;

    void resetCore() override;

public:
    Qt::KeyboardModifiers zoomH;
    Qt::KeyboardModifiers zoomV;
    Qt::KeyboardModifiers moveH;
    Qt::KeyboardModifiers zoomWaveH;
    Qt::KeyboardModifiers selectR;
    Qt::KeyboardModifiers selectC;
    Qt::KeyboardModifiers sceneDrag;
    Qt::KeyboardModifiers stretchA;
    Qt::KeyboardModifiers stretchR;
    Qt::KeyboardModifiers strecthP;
};

#endif // CONFIGFILE_H
