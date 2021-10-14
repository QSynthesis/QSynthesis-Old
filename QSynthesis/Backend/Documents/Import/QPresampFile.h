#ifndef QPRESAMPFILE_H
#define QPRESAMPFILE_H

#include "QSettingFile.h"

// Reference: https://sp.ch.nicovideo.jp/delta_kimigatame/blomaga/ar483589

class QPresampFile {
public:
    QPresampFile();
    ~QPresampFile();

    enum Locale { Japanese, English, Korean, TraditionalChinese };

    static const QString KEY_NAME_VERSION;
    static const QString KEY_NAME_LOCALE;
    static const QString KEY_NAME_RESAMP;
    static const QString KEY_NAME_TOOL;
    static const QString KEY_NAME_VOWEL;
    static const QString KEY_NAME_CONSONANT;
    static const QString KEY_NAME_PRIORITY;
    static const QString KEY_NAME_REPLACE;
    static const QString KEY_NAME_ALIAS;
    static const QString KEY_NAME_PREFIX;
    static const QString KEY_NAME_SUFFIX;
    static const QString KEY_NAME_NOTE_NUM;
    static const QString KEY_NAME_APPEND;
    static const QString KEY_NAME_PITCH;
    static const QString KEY_NAME_ALIAS_PRIORITY;
    static const QString KEY_NAME_ALIAS_PRIORITY_DIFAPPEND;
    static const QString KEY_NAME_ALIAS_PRIORITY_DIFPITCH;
    static const QString KEY_NAME_SPLIT;
    static const QString KEY_NAME_MUST_VC;
    static const QString KEY_NAME_C_FLAGS;
    static const QString KEY_NAME_VC_LENGTH;
    static const QString KEY_NAME_ENDTYPE;
    static const QString KEY_NAME_ENDTYPE1;
    static const QString KEY_NAME_ENDTYPE2;
    static const QString KEY_NAME_VC_PAD;
    static const QString KEY_NAME_ENDFLAG;
    static const QString KEY_NAME_BATNUM;

public:
    bool load(const QString &filename);
    bool save(const QString &filename);

private:
};

#endif // QPRESAMPFILE_H
