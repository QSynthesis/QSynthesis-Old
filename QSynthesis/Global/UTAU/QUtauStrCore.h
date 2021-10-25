#ifndef QUTAUSTRCORE_H
#define QUTAUSTRCORE_H

#include "Strings/UtaFilenames.h"
#include "Strings/UtaProjectText.h"
#include "Strings/UtaSettingIni.h"

// Supplements
namespace UtaSettingIni {

    const QString KEY_PREFIX_VOICE = "Voice";
    const QString KEY_PREFIX_WAVTOOL = "Wavtool";
    const QString KEY_PREFIX_RESAMPLER = "Resampler";

    const QString KEY_NAME_LAST_QUANTIZE = "LastQuantize";
    const QString KEY_NAME_FORMS_VISIBILITY = "FormsVisibility";
    const QString KEY_NAME_ELEMENTS_STATE = "ElementsState";
    const QString KEY_NAME_PLAYHEAD_STATE = "PlayheadState";
    const QString KEY_NAME_FOREGROUND_STATE = "ForegroundState";
    const QString KEY_NAME_THEME_INDEX = "ThemeIndex";

    const QString KEY_NAME_INSERT_LYRICS_STATE = "InsertLyricsState";

    const QString SECTION_NAME_TEMP = "Temporary";
    const QString SECTION_NAME_GUI = "GUI";
    const QString SECTION_NAME_PROJECT = "Histories";
    const QString SECTION_NAME_VOICE = "Voices";
    const QString SECTION_NAME_WAVTOOL = "Wavtools";
    const QString SECTION_NAME_RESAMPLER = "Resamplers";

} // namespace UtaSettingText

QString fromUSTVoiceDir(const QString &filePath, const QString &appPath);

QString toUSTVoiceDir(const QString &filePath, const QString &appPath);

QString fromUSTToolsDir(const QString &filePath, const QString &appPath);

QString toUSTToolsDir(const QString &filePath, const QString &appPath);

#endif // QUTAUSTRCORE_H
