#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QRectF>
#include <QString>

const QString Version = "0.1.86";

// Inner wavetool arguments
const int SampleRate = 44100;
const int SampleBits = 16;
const int Channels = 1;

// No defined
const QRect NO_RECT = QRect(0, 0, 0, 0);
const QRectF NO_RECTF = QRectF(0, 0, 0, 0);

// Modules
const QString CLIPBOARD_FORMAT_NAME_NOTE = "qsynthesis/notes";

const QString FILE_HEAD_DUMP = "qsdump";

const QString DIR_NAME_TEMP = "QSyntehsis_Temporary";
const QString DIR_NAME_TEMP_PREFIX = "qs";
const QString KEY_NAME_MEMORY_PREFIX = "QSynthesis_Memory_";

// File and dir names
const QString FILE_NAME_SETTING_JSON = "config.json";
const QString FILE_NAME_KEYBOARD_JSON = "keyboard.json";

const QString FILE_NAME_HISTORY_DAT = "history.dat";
const QString FILE_NAME_INFO_JSON = "info.json";

const QString DIR_NAME_TEMP_CACHE = "cache";

const QString DIR_NAME_CONFIG = "config";
const QString DIR_NAME_CONFIG_THEMES = "themes";
const QString DIR_NAME_CONFIG_LANGUAGES = "translations";
const QString DIR_NAME_CONFIG_FONTS = "fonts";

#endif // CONSTANTS_H
