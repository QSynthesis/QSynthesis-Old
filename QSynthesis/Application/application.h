#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDebug>
#include <QMouseEvent>

#include "ConfigFile.h"
#include "Managers/ColorTheme.h"
#include "Managers/DataManager.h"
#include "Managers/MemoryManager.h"
#include "Managers/PluginManager.h"
#include "Managers/VoiceManager.h"
#include "MiniSystem/MiniSystem.h"
#include "SettingIniFile.h"
#include "ShortcutsFile.h"

#ifdef qApp
#undef qApp
#endif
#define qApp (qobject_cast<Application *>(QCoreApplication::instance()))

#define qSystem qApp->system()
#define qShortcuts qApp->shortcuts()
#define qSetting qApp->settingIni()
#define qConfig qApp->config()
#define qData qApp->data()
#define qPlugins qApp->plugins()
#define qVoice qApp->voice()
#define qMemory qApp->memory()
#define qTheme qApp->theme()

class Application : public QApplication {
    Q_OBJECT
public:
#ifdef Q_QDOC
    Application(int &argc, char **argv);
#else
    Application(int &argc, char **argv, int flag = ApplicationFlags);
#endif
    virtual ~Application();

private:
    void initApp();
    void quitApp();

protected:
    bool notify(QObject *obj, QEvent *event) override;

    // Singletons
public:
    MiniSystem *system() const;

    ShortcutsFile *shortcutsDeafult() const;

    ShortcutsFile *shortcuts() const;
    SettingIniFile *settingIni() const;
    ConfigFile *config() const;

    DataManager *data() const;
    PluginManager *plugins() const;
    VoiceManager *voice() const;
    MemoryManager *memory() const;
    ColorTheme *theme() const;

public:
    static QString tempDir();

protected:
    MiniSystem *m_system;

    ShortcutsFile *m_defShortcuts;

    ShortcutsFile *m_shortcuts;
    SettingIniFile *m_settingIni;
    ConfigFile *m_config;

    DataManager *m_data;
    PluginManager *m_plugins;
    VoiceManager *m_voice;
    MemoryManager *m_memory;
    ColorTheme *m_theme;

signals:
    void signal_mousePress(QMouseEvent *event);
    void signal_mouseMove(QMouseEvent *event);
    void signal_mouseRelease(QMouseEvent *event);
};


#endif // APPLICATION_H
