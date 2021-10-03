#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QKeyEvent>
#include <QTranslator>

#include "Macros.h"
#include "application.h"

#define qData DataManager::instance()

class DataManager : public QObject {
    Q_OBJECT
    Q_SINGLETON(DataManager)
public:
    explicit DataManager(QObject *parent = nullptr);
    ~DataManager();

public:
    void reloadStrings();

    // Keys
public:
    static bool keyIsDown(QEvent *event);
    static bool isUnusableKey(Qt::Key key);
    static bool isSpecialKey(Qt::Key key);
    static bool isModifierKey(Qt::Key key);
    static bool isSpecialShortcut(QKeySequence shortcut);

    // Translators
public:
    static bool translate(const QString &filename);
    static void eliminate();

private:
    static QList<QTranslator *> Translators;
};

#endif // DATAMANAGER_H
