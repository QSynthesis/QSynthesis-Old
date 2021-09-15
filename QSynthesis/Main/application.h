#ifndef APPLICATION_H
#define APPLICATION_H

#define qApp (qobject_cast<Application *>(QCoreApplication::instance()))

#include <QApplication>
#include <QDebug>
#include <QMouseEvent>

class Application : public QApplication {
    Q_OBJECT
public:
#ifdef Q_QDOC
    Application(int &argc, char **argv);
#else
    Application(int &argc, char **argv, int flag = ApplicationFlags);
#endif
    virtual ~Application();

protected:
    bool notify(QObject *obj, QEvent *event) override;

signals:
    void signal_mousePress(QMouseEvent *event);
    void signal_mouseMove(QMouseEvent *event);
    void signal_mouseRelease(QMouseEvent *event);
};


#endif // APPLICATION_H
