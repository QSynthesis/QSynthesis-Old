#include "VoiceInfo.h"
#include "QUtauStrings.h"
#include "Strings/UtaCharacterText.h"
#include "Utils/CharsetHandler.h"

using namespace UtaCharacterText;

QTextCodec *VoiceInfo::defaultCodec = nullptr;

VoiceInfo::VoiceInfo(QObject *parent) : DirectoryManager(parent) {
    init();
    reset();
}

VoiceInfo::VoiceInfo(const QString &dir, QObject *parent) : DirectoryManager(parent) {
    init();
    setDirname(dir);
}

VoiceInfo::~VoiceInfo() {
}

QTextCodec *VoiceInfo::codec() const {
    return m_codec;
}

void VoiceInfo::setCodec(QTextCodec *codec) {
    m_codec = codec;
}

void VoiceInfo::init() {
    m_codec = defaultCodec;
    connect(&charTxt, &NormalFile::changed, this, &VoiceInfo::handleCharTxtChanged);
}

bool VoiceInfo::loadCore() {
    if (!isDirExist(m_dirname)) {
        return false;
    }
    return loadCharTxt();
}

bool VoiceInfo::saveCore() {
    if (!isDirExist(m_dirname)) {
        return false;
    }
    return saveCharTxt();
}

QString VoiceInfo::name() const {
    return m_name;
}

QString VoiceInfo::title() const {
    if (m_name.isEmpty()) {
        return PathFindFileName(m_dirname);
    } else {
        return m_name;
    }
}

QString VoiceInfo::author() const {
    return m_author;
}

QString VoiceInfo::image() const {
    return m_image;
}

void VoiceInfo::setName(const QString &name) {
    m_name = name;
}

void VoiceInfo::setAuthor(const QString &author) {
    m_author = author;
}

void VoiceInfo::setImage(const QString &image) {
    m_image = image;
}

void VoiceInfo::resetCore() {
    m_name = "";
    m_author = "";
    m_image = "";
}

void VoiceInfo::prepareCore() {
    charTxt.setFilename(m_dirname + Slash + FILE_NAME_CHAR_TEXT);
}

bool VoiceInfo::loadCharTxt() {
    if (!charTxt.load()) {
        return false;
    }

    QByteArray data = charTxt.data();
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

        if (key == KEY_NAME_CHAR_NAME) {
            m_name = value;
        } else if (key == KEY_NAME_CHAR_AUTHOR) {
            m_author = value;
        } else if (key == KEY_NAME_CHAR_IMAGE) {
            m_image = QDir::fromNativeSeparators(value);
        } else {
            m_custom.append(line);
        }
    }

    return true;
}

bool VoiceInfo::saveCharTxt() {
    QByteArray data;
    QTextStream out(&data);
    out.setCodec(m_codec);

    if (!m_name.isEmpty()) {
        out << KEY_NAME_CHAR_NAME << "=" << m_name << Qt::endl;
    }
    if (!m_image.isEmpty()) {
        out << KEY_NAME_CHAR_IMAGE << "=" << QDir::toNativeSeparators(m_image) << Qt::endl;
    }
    if (!m_author.isEmpty()) {
        out << KEY_NAME_CHAR_AUTHOR << "=" << m_author << Qt::endl;
    }

    for (QString &line : m_custom) {
        out << line << Qt::endl;
    }

    charTxt.setData(data);
    return charTxt.save();
}

void VoiceInfo::handleChangedCore() {
}

void VoiceInfo::handleCharTxtChanged() {
    if (m_autoReload) {
        resetCore();
        loadCharTxt();
    }
    emit charTxtChanged();
}

QTextCodec *VoiceInfo::codeForDefault() {
    return defaultCodec;
}

void VoiceInfo::setCodeForDefault(QTextCodec *codec) {
    defaultCodec = codec;
}
