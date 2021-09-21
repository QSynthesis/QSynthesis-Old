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

public:
    static bool translate(const QString &filename);
    static void eliminate();

private:
    static QList<QTranslator *> Translators;

};

#endif // APPASSISTANT_H
