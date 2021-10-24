#include "Variables.h"
#include "Macros.h"
#include "QUtauStrings.h"

QString Version = "0.1.86";
QString TempDirName = "QSyntehsis_Temporary";

QString AppPath;
QString AppFontName;

QString MainTitle;
QString WindowTitle;
QString ErrorTitle;
QString UntitledFileName;
QString UntitledPrefix;
QString DeletedPrefix;

QString fileManagerName;

QString openFilterString;
QString saveFilterString;
QString importFilterString;
QString appendFilterString;
QString exportSelectionFilterString;
QString exportTrackFilterString;
QString exportOtoIniFilterString;
QString imageFilterString;
QString audioFilterString;
QString toolsFilterString;

QString voiceProfile() {
    return AppPath + Slash + DIR_NAME_VOICE;
}

QString pluginsProfile() {
    return AppPath + Slash + DIR_NAME_PLUGIN;
}

QString configProfile() {
    return AppPath + Slash + DIR_NAME_CONFIG;
}
QString themesProfile() {
    return configProfile() + Slash + DIR_NAME_CONFIG_THEMES;
}

QString languagesProfile() {
    return configProfile() + Slash + DIR_NAME_CONFIG_LANGUAGES;
}

QString fontsProfile() {
    return configProfile() + Slash + DIR_NAME_CONFIG_FONTS;
}

QString settingConifgPath() {
    return configProfile() + Slash + FILE_NAME_SETTING_JSON;
}

QString keyboardConfigPath() {
    return configProfile() + Slash + FILE_NAME_KEYBOARD_JSON;
}

QString settingIniPath() {
    return AppPath + Slash + FILE_NAME_SETTING_INI;
}
