#include "total.h"
#include "Document/ConfigFile.h"
#include "Document/PluginInfo.h"
#include "Document/SequenceTextFile.h"
#include "Document/SettingIniFile.h"
#include "Document/ShortcutsFile.h"
#include "Document/VoiceInfo.h"
#include "Managers/MemoryManager.h"
#include "Managers/PluginManager.h"
#include "Managers/VoiceManager.h"
#include "VoiceBank/QOtoIni.h"
#include "VoiceBank/QPrefixMap.h"
#include "VoiceBank/QReadmeText.h"

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

void initSingletons() {
    MiniSystem::createCase();

    ShortcutsFile::createDefault();

    SettingIniFile::createCase();
    ConfigFile::createCase();
    ShortcutsFile::createCase();
    DataManager::createCase();

    PluginManager::createCase();
    VoiceManager::createCase();
    MemoryManager::createCase();
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

void removeSingletons() {
    PluginManager::destroyCase();
    VoiceManager::destroyCase();
    MemoryManager::destroyCase();

    SettingIniFile::destroyCase();
    ConfigFile::destroyCase();
    ShortcutsFile::destroyCase();
    DataManager::destroyCase();

    ShortcutsFile::removeDefault();

    MiniSystem::destroyCase();
}

void created() {
    MainTitle = "QSynthesis For UTAU";
    WindowTitle = MainTitle + QString(" v%1").arg(Version);
    UntitledPrefix = "*";
    AppPath = QDir::currentPath();

    initFonts();
    initLocale();
    initSingletons();
}

void destroyed() {
    removeSingletons();
}
