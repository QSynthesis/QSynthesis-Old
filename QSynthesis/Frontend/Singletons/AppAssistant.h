#ifndef APPASSISTANT_H
#define APPASSISTANT_H

#include <QKeyEvent>
#include <QTranslator>

#include "Macros.h"
#include "application.h"

class AppAssistant : public QObject {
    Q_OBJECT
    Q_SINGLETON(AppAssistant)
public:
    explicit AppAssistant(QObject *parent = nullptr);
    ~AppAssistant();

public:
    static bool keyIsDown(QEvent *event);

private:
    static QList<QTranslator *> Translators;

public:
    static bool translate(const QString &filename) {
        QTranslator *t = new QTranslator(self);
        if (t->load(filename)) {
            qApp->installTranslator(t);
            Translators.append(t);
            return true;
        }
        delete t;
        return false;
    }

    static void eliminate() {
        for (QTranslator *t : Translators) {
            qApp->removeTranslator(t);
            delete t;
        }
        Translators.clear();
    }
};

#endif // APPASSISTANT_H
