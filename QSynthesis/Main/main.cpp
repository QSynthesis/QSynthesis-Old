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

    QTranslator t;
    if (t.load(":/translations/qsynthesis_cn.qm")) {
        qApp->installTranslator(&t);
    }

    created(); // Create

    MainWindow w;
    w.initAndShow();
    w.fromCommandLine(argc, argv);

    int code = a.exec();

    w.quitWindow();

    destroyed(); // Destroy

    return code;
}
