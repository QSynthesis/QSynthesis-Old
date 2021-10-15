#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QKeyEvent>
#include <QTranslator>

#include "Macros.h"

class DataManager : public QObject {
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
    ~DataManager();

public:
    bool load();

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
    bool translate(const QString &filename);
    void eliminate();

private:
    QList<QTranslator *> Translators;
};

#endif // DATAMANAGER_H
