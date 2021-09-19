#include "application.h"
#include "total.h"

int main(int argc, char *argv[]) {
    Application a(argc, argv);

#if defined(Q_OS_MAC)
    QDir bin(QCoreApplication::applicationDirPath());
    bin.cdUp(); /* Fix this on Mac because of the .app folder, */
    bin.cdUp(); /* which means that the actual executable is   */
    bin.cdUp(); /* three levels deep. Grrr.                    */
    QDir::setCurrent(bin.absolutePath());
#elif defined(Q_OS_WINDOWS)
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
#endif

    created(); // Create

    AppAssistant::translate(":/translations/qsynthesis_cn.qm");
#if defined(Q_OS_MAC)
#else
    AppAssistant::translate(QCoreApplication::applicationDirPath() + "/translations/qt_zh_CN.qm");
    AppAssistant::translate(QCoreApplication::applicationDirPath() + "/translations/qt_help_zh_CN.qm");
#endif

    MainWindow w;
    w.initAndShow();
    w.fromCommandLine(argc, argv);

    int code = a.exec();

    w.quitWindow();

    destroyed(); // Destroy

    return code;
}
