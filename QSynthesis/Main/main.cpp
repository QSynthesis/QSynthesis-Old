#include "Managers/ClientManager.h"
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

    //    ClientManager c;
    //    if (c.tryCallServer()) {
    //        return 1;
    //    }
    //    if (!c.startAsServer()) {
    //        return -1;
    //    }

    created(); // Create

    qData->translate(":/translations/qsynthesis_cn.qm");
#if defined(Q_OS_MAC)
    qData->translate(AppPath + "/translations/qt_zh_CN.qm");
#else
    qData->translate(QCoreApplication::applicationDirPath() + "/translations/qt_zh_CN.qm");
#endif

    MainWindow w;
    w.initAndShow();
    w.fromCommandLine(a.arguments());

    int code = a.exec();

    w.freeAndQuit();

    destroyed(); // Destroy

    return code;
}
