#include "application.h"

#ifdef Q_QDOC
Application::Application(int m_argc, char **argv) : QApplication(argc, argv) {
    init();
}
#else
Application::Application(int &argc, char **argv, int flag) : QApplication(argc, argv, flag) {
    initApp();
}
#endif

Application::~Application() {
    quitApp();
}

void Application::initApp() {
    m_system = new MiniSystem();

    m_defShortcuts = new ShortcutsFile(Qs::Default);
    m_shortcuts = new ShortcutsFile(Qs::Default);

    m_settingIni = new SettingIniFile();
    m_config = new ConfigFile();

    m_data = new DataManager();
    m_plugins = new PluginManager();
    m_voice = new VoiceManager();
    m_memory = new MemoryManager();
    m_theme = new ColorTheme();
}

void Application::quitApp() {
    m_system->deleteLater();

    delete m_defShortcuts;
    delete m_shortcuts;

    delete m_settingIni;
    delete m_config;

    m_data->deleteLater();
    m_plugins->deleteLater();
    m_voice->deleteLater();
    m_memory->deleteLater();
    delete m_theme;
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

MiniSystem *Application::system() const {
    return m_system;
}

ShortcutsFile *Application::shortcutsDeafult() const {
    return m_defShortcuts;
}

ShortcutsFile *Application::shortcuts() const {
    return m_shortcuts;
}

SettingIniFile *Application::settingIni() const {
    return m_settingIni;
}

ConfigFile *Application::config() const {
    return m_config;
}

DataManager *Application::data() const {
    return m_data;
}

PluginManager *Application::plugins() const {
    return m_plugins;
}

VoiceManager *Application::voice() const {
    return m_voice;
}

MemoryManager *Application::memory() const {
    return m_memory;
}

ColorTheme *Application::theme() const {
    return m_theme;
}

QString Application::tempDir() {
    return qMemory->tempDir();
}

void Application::exitOnPermissionDenied() {
    QMessageBox::critical(nullptr, ErrorTitle, tr("No write file permission!"));
    exit(1);
}
