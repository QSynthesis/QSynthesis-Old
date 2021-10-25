#ifndef UTAFILENAMES_H
#define UTAFILENAMES_H

#include <QString>

namespace UtaFilenames {

    const QString FILE_NAME_PLUGIN_TEXT = "plugin.txt";
    const QString FILE_NAME_CHAR_TEXT = "character.txt";

    const QString FILE_NAME_VOICE_README = "readme.txt";
    const QString FILE_NAME_OTO_INI = "oto.ini";
    const QString FILE_NAME_PREFIX_MAP = "prefix.map";

    const QString FILE_NAME_TEMP_AUDIO = "temp.wav";

    const QString FILE_NAME_SETTING_INI = "setting.ini";

// Cross-platform File Names
#ifdef Q_OS_WINDOWS
    const QString FILE_NAME_TEMP_BATCH = "temp.bat";
    const QString FILE_NAME_HELPER_BATCH = "temp_helper.bat";
#elif defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    const QString FILE_NAME_TEMP_BATCH = "temp.sh";
    const QString FILE_NAME_HELPER_BATCH = "temp_helper.sh";
#endif

    const QString DIR_NAME_VOICE = "voice";
    const QString DIR_NAME_PLUGIN = "plugins";

} // namespace UtaFilenames

#endif // UTAFILENAMES_H
