#include "QPresampFile.h"

const QString QPresampFile::KEY_NAME_VERSION = "VERSION";
const QString QPresampFile::KEY_NAME_LOCALE = "LOCALE";
const QString QPresampFile::KEY_NAME_RESAMP = "RESAMP";
const QString QPresampFile::KEY_NAME_TOOL = "TOOL";
const QString QPresampFile::KEY_NAME_VOWEL = "VOWEL";
const QString QPresampFile::KEY_NAME_CONSONANT = "CONSONANT";
const QString QPresampFile::KEY_NAME_PRIORITY = "PRIORITY";
const QString QPresampFile::KEY_NAME_REPLACE = "REPLACE";
const QString QPresampFile::KEY_NAME_ALIAS = "ALIAS";
const QString QPresampFile::KEY_NAME_PREFIX = "PRE";
const QString QPresampFile::KEY_NAME_SUFFIX = "SU";
const QString QPresampFile::KEY_NAME_NOTE_NUM = "NUM";
const QString QPresampFile::KEY_NAME_APPEND = "APPEND";
const QString QPresampFile::KEY_NAME_PITCH = "PITCH";
const QString QPresampFile::KEY_NAME_ALIAS_PRIORITY = "ALIAS_PRIORITY";
const QString QPresampFile::KEY_NAME_ALIAS_PRIORITY_DIFAPPEND = "ALIAS_PRIORITY_DIFAPPEND";
const QString QPresampFile::KEY_NAME_ALIAS_PRIORITY_DIFPITCH = "ALIAS_PRIORITY_DIFPITCH";
const QString QPresampFile::KEY_NAME_SPLIT = "SPLIT";
const QString QPresampFile::KEY_NAME_MUST_VC = "MUSTVC";
const QString QPresampFile::KEY_NAME_C_FLAGS = "CFLAGS";
const QString QPresampFile::KEY_NAME_VC_LENGTH = "VCLENGTH";
const QString QPresampFile::KEY_NAME_ENDTYPE = "ENDTYPE";
const QString QPresampFile::KEY_NAME_ENDTYPE1 = "ENDTYPE1";
const QString QPresampFile::KEY_NAME_ENDTYPE2 = "ENDTYPE2";
const QString QPresampFile::KEY_NAME_VC_PAD = "VCPAD";
const QString QPresampFile::KEY_NAME_ENDFLAG = "ENDFLAG";
const QString QPresampFile::KEY_NAME_BATNUM = "BATNUM";

QPresampFile::QPresampFile() {
}

QPresampFile::~QPresampFile() {
}

bool QPresampFile::load(const QString &filename) {
    QSettingFile setting;
    if (!setting.load(filename)) {
        return false;
    }
    return true;
}

bool QPresampFile::save(const QString &filename) {
    QSettingFile setting;
    return setting.save(filename);
}
