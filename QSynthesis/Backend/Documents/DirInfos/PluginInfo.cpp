#include "PluginInfo.h"
#include "NormalFile.h"
#include "QSettingFile.h"
#include "QUtauStrings.h"
#include "QUtils.h"
#include "Strings/UtaPluginText.h"
#include "Utils/CharsetHandler.h"

using namespace UtaPluginText;

Q_CHARSET_DECLARE(PluginInfo)

PluginInfo::PluginInfo() : BaseDirInfo(Qs::Default) {
    init();
    reset();
}

PluginInfo::PluginInfo(const QString &dirname) : BaseDirInfo(Qs::Default) {
    init();
    setDirname(dirname);
}

PluginInfo::~PluginInfo() {
}

PluginInfo::PluginInfo(Qs::VariableSource source) {
    init();
}

void PluginInfo::init() {
    m_codec = defaultCodec;
}

bool PluginInfo::loadCore(bool *valid) {
    NormalFile file(filename());
    if (!file.load()) {
        return false;
    }

    QByteArray data = file.data();
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

bool PluginInfo::saveCore() {
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

    NormalFile file(filename());
    file.setData(data);
    return file.save();
}

bool PluginInfo::useShell() const {
    return m_useShell;
}

QString PluginInfo::exePath() const {
    return m_filename + Slash + m_execute;
}

void PluginInfo::setExePath(const QString &path) {
    m_execute = PathFindFileName(path, m_filename);
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

QString PluginInfo::infoFilename() const {
    return FILE_NAME_PLUGIN_TEXT;
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
