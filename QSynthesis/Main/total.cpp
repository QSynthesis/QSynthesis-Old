#include "total.h"

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
    VoiceInfo::setCodeForDefault(gbk);        // character.txt
    PluginInfo::setCodeForDefault(gbk);       // plugin.txt
    QReadmeText::setCodeForDefault(gbk);      // readme.txt
}

void initSingletons() {
    SettingIniData::createCase();
    ConfigData::createCase();
    ShortcutsData::createCase();

    ColorTheme::createCase();
}

void removeSingletons() {
    SettingIniData::destroyCase();
    ConfigData::destroyCase();
    ShortcutsData::destroyCase();

    ColorTheme::destroyCase();
}

void created() {
    MainTitle = QString("QSynthesis For UTAU v%1").arg(Version);
    UntitledPrefix = "*";
    AppPath = QDir::currentPath();

    initLocale();
    initSingletons();

    MainWindow::checkWorkingDir();
    MainWindow::checkTemporaryDir();

    MainWindow::initConfigData();
    MainWindow::initShortcutsData();
    MainWindow::initSettingIni();

    MainWindow::initVoice();
    MainWindow::initPlugins();
    MainWindow::initThemes();
    MainWindow::initLanguages();
}

void destroyed() {
    MainWindow::exitPreparation();
    MainWindow::saveSettingIni();

    removeSingletons();
}
