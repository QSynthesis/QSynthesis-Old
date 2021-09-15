#include "application.h"

#ifdef Q_QDOC
Application::Application(int &argc, char **argv) : QApplication(argc, argv) {
}
#else
Application::Application(int &argc, char **argv, int flag) : QApplication(argc, argv, flag) {
}
#endif

Application::~Application() {
}

bool Application::notify(QObject *obj, QEvent *event) {
    switch (event->type()) {
    case QEvent::MouseButtonRelease:
        emit signal_mouseRelease(static_cast<QMouseEvent *>(event));
        break;
    case QEvent::MouseMove:
        emit signal_mouseMove(static_cast<QMouseEvent *>(event));
        break;
    case QEvent::MouseButtonPress:
        emit signal_mousePress(static_cast<QMouseEvent *>(event));
        break;
    default:
        break;
    }
    return QApplication::notify(obj, event);
}
