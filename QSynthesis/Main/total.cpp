#include "total.h"
#include "ConfigFile.h"
#include "Managers/MemoryManager.h"
#include "Managers/PluginManager.h"
#include "Managers/VoiceManager.h"
#include "PluginInfo.h"
#include "SequenceTextFile.h"
#include "SettingIniFile.h"
#include "ShortcutsFile.h"
#include "VoiceBank/QOtoIni.h"
#include "VoiceBank/QPrefixMap.h"
#include "VoiceBank/QReadmeText.h"
#include "VoiceInfo.h"

void initLocale() {
    QTextCodec *loc;
#ifdef Q_OS_WINDOWS
    loc = QTextCodec::codecForName("UTF-8");
#else
    loc = QTextCodec::codecForLocale();
#endif
    SettingIniFile::setCodeForDefault(loc);

    QTextCodec *gbk = QTextCodec::codecForName("GBK");

    SequenceTextFile::setCodeForDefault(gbk); // *.ust
    QOtoIni::setCodeForDefault(gbk);          // oto.ini
    QPrefixMap::setCodeForDefault(gbk);       // prefix.map
    VoiceInfo::setCodeForDefault(gbk);        // character.txt
    PluginInfo::setCodeForDefault(gbk);       // plugin.txt
    QReadmeText::setCodeForDefault(gbk);      // readme.txt
}

void initFonts() {
    QString fonts = fontsProfile();
#ifdef Q_OS_MAC
    AppFontName = qApp->font().family();
#else
    QFontDatabase::addApplicationFont(fonts + Slash + "msyh.ttc");
    QFontDatabase::addApplicationFont(fonts + Slash + "msyhbd.ttc");
    QFontDatabase::addApplicationFont(fonts + Slash + "msyhl.ttc");
    AppFontName = "Microsoft YaHei UI";
    qApp->setFont(mainFont());
#endif
}

void created() {
    MainTitle = "QSynthesis For UTAU";
    WindowTitle = MainTitle + QString(" v%1").arg(Version);
    UntitledPrefix = "*";
    AppPath = QDir::currentPath();

    initFonts();
    initLocale();
}

void destroyed() {
}
