#ifndef VARIABLES_H
#define VARIABLES_H

#include <QApplication>
#include <QString>

class PluginsCollect;
class VoiceCollect;
class NormalFileCollect;

extern QString Version;
extern QString TempDirName;

extern QString AppPath;
extern QString AppFontName;

extern QString MainTitle;
extern QString WindowTitle;
extern QString ErrorTitle;
extern QString UntitledFileName;
extern QString UntitledPrefix;
extern QString DeletedPrefix;

extern PluginsCollect *plugins;
extern VoiceCollect *voice;
extern NormalFileCollect *themes;
extern NormalFileCollect *languages;

extern QString openFilterString;
extern QString saveFilterString;
extern QString importFilterString;
extern QString appendFilterString;
extern QString exportSelectionFilterString;
extern QString exportTrackFilterString;
extern QString exportOtoIniFilterString;
extern QString imageFilterString;
extern QString audioFilterString;
extern QString toolsFilterString;

extern QString tempDirectoryName;

QString voiceProfile();
QString pluginsProfile();
QString configProfile();
QString themesProfile();
QString languagesProfile();
QString fontsProfile();

QString settingConifgPath();
QString keyboardConfigPath();
QString settingIniPath();

#endif // VARIABLES_H
