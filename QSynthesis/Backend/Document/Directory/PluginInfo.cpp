#include "PluginInfo.h"
#include "PluginsCollect.h"
#include "QUtauStrings.h"
#include "Strings/UtaPluginText.h"
#include "Utils/CharsetHandler.h"

using namespace UtaPluginText;

QTextCodec *PluginInfo::defaultCodec = nullptr;

PluginInfo::PluginInfo(QObject *parent) : DirectoryManager(parent) {
    init();
    reset();
}

PluginInfo::PluginInfo(const QString &dir, QObject *parent) : DirectoryManager(parent) {
    init();
    setDirname(dir);
}

PluginInfo::~PluginInfo() {
}

QTextCodec *PluginInfo::codec() const {
    return m_codec;
}

void PluginInfo::setCodec(QTextCodec *codec) {
    m_codec = codec;
}

void PluginInfo::init() {
    m_codec = defaultCodec;
    connect(&pluginTxt, &NormalFile::changed, this, &PluginInfo::handlePluginTxtChanged);
}

bool PluginInfo::loadCore() {
    if (!isDirExist(m_dirname)) {
        return false;
    }

    return loadPluginTxt();
}

bool PluginInfo::saveCore() {
    if (!isDirExist(m_dirname)) {
        return false;
    }

    return savePluginTxt();
}

bool PluginInfo::useShell() const {
    return m_useShell;
}

QString PluginInfo::exePath() const {
    return m_dirname + Slash + m_execute;
}

void PluginInfo::setExePath(const QString &path) {
    m_execute = PathFindFileName(path, m_dirname);
}

QString PluginInfo::name() const {
    return m_name;
}

QString PluginInfo::ustVersion() const {
    return m_ustVersion;
}

void PluginInfo::resetCore() {
    m_useShell = false;
    m_ustVersion = "";
    m_name = "";
    m_execute = "";

    m_charset = "";

    m_allNote = false;
}

void PluginInfo::prepareCore() {
    pluginTxt.setFilename(m_dirname + Slash + FILE_NAME_PLUGIN_TEXT);
}

bool PluginInfo::loadPluginTxt() {
    if (!pluginTxt.load()) {
        return false;
    }

    QByteArray data = pluginTxt.data();
    QString charset = CharsetHandler::detectCharset(data);
    QTextStream in(&data);

    if (!charset.isEmpty()) {
        m_codec = QTextCodec::codecForName(charset.toLatin1());
    }
    in.setCodec(m_codec);

    QString line;
    int eq;
    QString key, value;

    while (!in.atEnd()) {
        line = in.readLine();
        if (line.isEmpty()) {
            continue;
        }

        eq = line.indexOf('=');
        if (eq < 0) {
            m_custom.append(line);
            continue;
        }

        key = line.mid(0, eq);
        value = line.mid(eq + 1);

        if (key == KEY_NAME_PLUGIN_NAME) {
            m_name = value;
        } else if (key == KEY_NAME_PLUGIN_EXECUTABLE) {
            m_execute = QDir::fromNativeSeparators(value);
        } else if (key == KEY_NAME_PLUGIN_UST_VERSION) {
            m_ustVersion = value;
        } else if (key == KEY_NAME_PLUGIN_SHELL && value == VALUE_NAME_PLUGIN_SHELL) {
            m_useShell = true;
        } else if (key == KEY_NAME_PLUGIN_NOTE && value == VALUE_NAME_PLUGIN_NOTE) {
            m_allNote = true;
        } else if (key == KEY_NAME_PLUGIN_CHARSET && !value.isEmpty()) {
            m_charset = value;
        } else {
            m_custom.append(line);
        }
    }

    return true;
}

bool PluginInfo::savePluginTxt() {
    QByteArray data;
    QTextStream out(&data);
    out.setCodec(m_codec);

    out << KEY_NAME_PLUGIN_NAME << "=" << m_name << Qt::endl;
    out << KEY_NAME_PLUGIN_EXECUTABLE << "=" << QDir::toNativeSeparators(m_execute) << Qt::endl;

    if (m_useShell) {
        out << KEY_NAME_PLUGIN_SHELL << "=" << VALUE_NAME_PLUGIN_SHELL << Qt::endl;
    }

    if (m_allNote) {
        out << KEY_NAME_PLUGIN_NOTE << "=" << VALUE_NAME_PLUGIN_NOTE << Qt::endl;
    }

    if (!m_ustVersion.isEmpty()) {
        out << KEY_NAME_PLUGIN_UST_VERSION << "=" << m_ustVersion << Qt::endl;
    }

    if (!m_charset.isEmpty()) {
        out << KEY_NAME_PLUGIN_CHARSET << "=" << m_charset << Qt::endl;
    }

    for (QString &line : m_custom) {
        out << line << Qt::endl;
    }

    pluginTxt.setData(data);
    return pluginTxt.save();
}

void PluginInfo::setUstVersion(const QString &ustVersion) {
    m_ustVersion = ustVersion;
}

void PluginInfo::setName(const QString &name) {
    m_name = name;
}

void PluginInfo::setCharset(const QString &charset) {
    m_charset = charset;
}

void PluginInfo::setAllNote(bool allNote) {
    m_allNote = allNote;
}

void PluginInfo::setUseShell(bool useShell) {
    m_useShell = useShell;
}

QStringList PluginInfo::custom() const {
    return m_custom;
}

void PluginInfo::setCustom(const QStringList &custom) {
    m_custom = custom;
}

void PluginInfo::handleChangedCore() {
}

void PluginInfo::handlePluginTxtChanged() {
    if (m_autoReload) {
        resetCore();
        loadPluginTxt();
    }
    emit pluginTxtChanged();
}

QString PluginInfo::charset() const {
    return m_charset;
}

bool PluginInfo::allNote() const {
    return m_allNote;
}

QTextCodec *PluginInfo::codeForDefault() {
    return defaultCodec;
}

void PluginInfo::setCodeForDefault(QTextCodec *codec) {
    defaultCodec = codec;
}
