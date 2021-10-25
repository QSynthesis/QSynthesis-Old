#include "Managers/ClientManager.h"
#include "application.h"
#include "total.h"

int main(int argc, char *argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Application a(argc, argv);

    created(); // Create

    MainWindow w;
    w.initAndShow();
    w.fromCommandLine(a.arguments());

    int code = a.exec();

    w.freeAndQuit();

    destroyed(); // Destroy

    return code;
}
