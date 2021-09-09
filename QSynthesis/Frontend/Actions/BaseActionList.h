#ifndef BASEACTIONLIST_H
#define BASEACTIONLIST_H

#include <QAction>
#include <QMenu>
#include <QObject>

class BaseActionList : public QObject {
    Q_OBJECT
public:
    explicit BaseActionList(QObject *parent = nullptr);
    virtual ~BaseActionList();

public:
    // File
    QAction *newFile;
    QAction *importFile;
    QAction *openFile;
    QAction *openFolder;
    QAction *saveFile;
    QAction *saveAsFile;
    QAction *restoreFile;
    QAction *switchFile;
    QAction *closeFile;

    QMenu *recentMenu; // *

    // Edit
    QAction *undo;
    QAction *redo;
    QAction *selectAll;
    QAction *deselect;

    // Modify
    QAction *reset;

    // Preview
    QAction *playPause;
    QAction *replay;
    QAction *stop;

    // Tools
    QAction *settings;
    QAction *keyShortcuts;
    QAction *themes;
    QAction *languages;

    QMenu *preferenceMenu;

    // Help
    QAction *welcome;
    QAction *instructions;
    QAction *checkUpdate;
    QAction *aboutApp;
    QAction *aboutQt;

public:
    void updateCommonStrings();
    void makeCommonDefaultShortcuts();
    QList<QAction *> commonActions() const;

    void setCommonActionsEnabled(bool enabled);

    QStringList commonNames() const;
    QList<QKeySequence> commonShortcuts() const;
    void setCommonShortcuts(const QList<QKeySequence> &keys) const;

public:
    virtual void setNaturalStatus();

    virtual void updateStrings();
    virtual void makeDefaultShortcuts();
    virtual QList<QAction *> actions() const;

    void setActionsEnabled(bool enabled);

    QStringList names() const;
    QList<QKeySequence> shortcuts() const;
    void setShortcuts(const QList<QKeySequence> &keys);

protected:
    void textToName(QAction *action, const QString &menu);
};

#endif // BASEACTIONLIST_H
