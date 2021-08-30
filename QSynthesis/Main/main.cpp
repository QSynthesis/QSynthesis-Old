#include <QApplication>

#include "QUtils.h"
#include "mainwindow.h"

void created() {
    QTextCodec *gbk = QTextCodec::codecForName("GBK");

    SequenceTextFile::setCodeForDefault(gbk); // *.ust
    QOtoIni::setCodeForDefault(gbk);          // oto.ini
    VoiceInfo::setCodeForDefault(gbk);        // character.txt
    PluginInfo::setCodeForDefault(gbk);       // plugin.txt
    QReadmeText::setCodeForDefault(gbk);      // readme.txt

    MainTitle = "QSynthesis For UTAU";
    UntitledPrefix = "*";
    AppPath = GetAppPath2();

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
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTranslator t;

    a.setFont(mainFont());
    translator = &t;
    if (translator->load(":/translations/qsynthesis_cn.qm")) {
        qApp->installTranslator(translator);
    }

    created(); // Create

    MainWindow w; // Create window
    w.initAndShow();
    w.fromCommandLine(argc, argv);

    int code = a.exec();

    destroyed(); // Destroy

    return code;
}
