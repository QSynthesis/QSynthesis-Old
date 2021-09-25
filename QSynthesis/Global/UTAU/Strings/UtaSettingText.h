#ifndef UTASETTINGTEXT_H
#define UTASETTINGTEXT_H

#include <QString>

namespace UtaSettingText {

    const QString KEY_NAME_CACHE_ENABLE = "CacheEnabled";
    const QString KEY_NAME_CACHE_DELETE_BY_SIZE = "CacheDeleteBySize";
    const QString KEY_NAME_CACHE_DELETE_SIZE = "CacheDeleteSize";
    const QString KEY_NAME_NO_OTO_REPORT = "NoOtoReport";
    const QString KEY_NAME_NO_COPY_GENON = "NoCopyVoiceParam";
    const QString KEY_NAME_NO_BATCH_MODE = "NoBatchMode";
    const QString KEY_NAME_PROCESSES = "Processes";
    const QString KEY_NAME_TOOL1_PATH = "Tool1Path";
    const QString KEY_NAME_TOOL2_PATH = "Tool2Path";

    const QString KEY_NAME_INSERT_LYRICS_STATE = "InsertLyricsState";

    const QString KEY_PREFIX_PROJECT = "History";
    const QString KEY_PREFIX_VOICE = "Voice";
    const QString KEY_PREFIX_WAVTOOL = "Wavtool";
    const QString KEY_PREFIX_RESAMPLER = "Resampler";

    const QString KEY_NAME_MAINWINDOW = "MainWindow";
    const QString KEY_NAME_LAST_QUANTIZE = "LastQuantize";
    const QString KEY_NAME_FORMS_VISIBILITY = "FormsVisibility";
    const QString KEY_NAME_ELEMENTS_STATE = "ElementsState";
    const QString KEY_NAME_PLAYHEAD_STATE = "PlayheadState";
    const QString KEY_NAME_FOREGROUND_STATE = "ForegroundState";
    const QString KEY_NAME_THEME_INDEX = "ThemeIndex";

    const QString SECTION_NAME_TEMP = "Temporary";
    const QString SECTION_NAME_GUI = "GUI";
    const QString SECTION_NAME_PROJECT = "Histories";
    const QString SECTION_NAME_VOICE = "Voices";
    const QString SECTION_NAME_WAVTOOL = "Wavtools";
    const QString SECTION_NAME_RESAMPLER = "Resamplers";

} // namespace UtaSettingText

#endif // UTASETTINGTEXT_H
