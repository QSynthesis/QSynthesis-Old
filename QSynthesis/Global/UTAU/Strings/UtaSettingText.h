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

    const QString KEY_NAME_LAST_QUANTIZE = "LastQuantize";
    const QString KEY_NAME_INSERT_IGNORE_RESTS = "IgnoreRestWhenInsert";
    const QString KEY_NAME_INSERT_REPLACE_LYRICS = "ReplaceLyricsWhenInsert";
    const QString KEY_NAME_INSERT_SEPARATE_CHAR = "SeparateCharWhenInsert";
    const QString KEY_NAME_TRACKS_FORM_VISIBILITY = "TracksFormVisibility";
    const QString KEY_NAME_EDITOR_FORM_VISIBILITY = "EditorFormVisibility";
    const QString KEY_NAME_PARAMS_FORM_VISIBILITY = "ParamsFormVisibility";
    const QString KEY_NAME_THEME_INDEX= "ThemeIndex";

    const QString KEY_PREFIX_PROJECT = "History";
    const QString KEY_PREFIX_VOICE = "Voice";
    const QString KEY_PREFIX_WAVTOOL = "Wavtool";
    const QString KEY_PREFIX_RESAMPLER = "Resampler";

    const QString KEY_NAME_MAINWINDOW = "MainWindow";

    const QString SECTION_NAME_TEMP = "Temporary";
    const QString SECTION_NAME_GUI = "GUI";
    const QString SECTION_NAME_PROJECT = "Histories";
    const QString SECTION_NAME_VOICE = "Voices";
    const QString SECTION_NAME_WAVTOOL = "Wavtools";
    const QString SECTION_NAME_RESAMPLER = "Resamplers";

} // namespace UtaSettingText

#endif // UTASETTINGTEXT_H
