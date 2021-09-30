#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "Files/BaseFile.h"
#include "Macros.h"

#define qConfig ConfigFile::instance()

class ConfigFile : public BaseFile {
    Q_SINGLETON(ConfigFile)
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
    Qt::KeyboardModifiers moveV;
    Qt::KeyboardModifiers selectR;
    Qt::KeyboardModifiers selectC;
    Qt::KeyboardModifiers sceneDrag;
    Qt::KeyboardModifiers stretchA;
    Qt::KeyboardModifiers stretchR;
    Qt::KeyboardModifiers strecthP;
};

#endif // CONFIGFILE_H
