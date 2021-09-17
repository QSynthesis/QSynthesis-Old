#include "PluginInfo.h"
#include "Import/QSettingFile.h"
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

    QStringList lines;
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }

    QSettingSection section;
    section.fromLines(lines);

    QString *nameValue = section.valueOf(KEY_NAME_PLUGIN_NAME);
    if (nameValue) {
        m_name = *nameValue;
    }
    QString *executeValue = section.valueOf(KEY_NAME_PLUGIN_EXECUTABLE);
    if (nameValue) {
        m_execute = QDir::fromNativeSeparators(*executeValue);
    }
    QString *versionValue = section.valueOf(KEY_NAME_PLUGIN_UST_VERSION);
    if (versionValue) {
        m_ustVersion = *versionValue;
    }
    QString *shellValue = section.valueOf(KEY_NAME_PLUGIN_SHELL);
    if (shellValue && *shellValue == VALUE_NAME_PLUGIN_SHELL) {
        m_useShell = true;
    }
    QString *noteValue = section.valueOf(VALUE_NAME_PLUGIN_NOTE);
    if (noteValue && *noteValue == VALUE_NAME_PLUGIN_NOTE) {
        m_allNote = true;
    }
    QString *charsetValue = section.valueOf(KEY_NAME_PLUGIN_CHARSET);
    if (charsetValue && !charsetValue->isEmpty()) {
        m_charset = *charsetValue;
    }
    m_custom = section.unformattedLines();

    return true;
}

bool PluginInfo::savePluginTxt() {
    QSettingSection section;
    section.addPair(KEY_NAME_PLUGIN_NAME, m_name);
    section.addPair(KEY_NAME_PLUGIN_EXECUTABLE, QDir::toNativeSeparators(m_execute));
    if (m_useShell) {
        section.addPair(KEY_NAME_PLUGIN_SHELL, VALUE_NAME_PLUGIN_SHELL);
    }
    if (m_allNote) {
        section.addPair(KEY_NAME_PLUGIN_NOTE, VALUE_NAME_PLUGIN_NOTE);
    }
    if (!m_ustVersion.isEmpty()) {
        section.addPair(KEY_NAME_PLUGIN_UST_VERSION, m_ustVersion);
    }
    if (!m_charset.isEmpty()) {
        section.addPair(KEY_NAME_PLUGIN_CHARSET, m_charset);
    }
    section.setUnformattedLines(m_custom);

    QStringList lines = section.toLines();

    QByteArray data;
    QTextStream out(&data);
    out.setCodec(m_codec);
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        out << *it << Qt::endl;
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

bool PluginInfo::valid() const {
    return isFileExist(exePath());
}

QTextCodec *PluginInfo::codeForDefault() {
    return defaultCodec;
}

void PluginInfo::setCodeForDefault(QTextCodec *codec) {
    defaultCodec = codec;
}
