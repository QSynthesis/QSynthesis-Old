#include "VoiceInfo.h"
#include "Import/QSettingFile.h"
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

bool VoiceInfo::valid() const {
    return isDirExist(m_dirname);
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

QString VoiceInfo::avatar() const {
    return m_avatar;
}

QString VoiceInfo::sprite() const {
    return m_sprite;
}

void VoiceInfo::setName(const QString &name) {
    m_name = name;
}

void VoiceInfo::setAuthor(const QString &author) {
    m_author = author;
}

void VoiceInfo::setAvatar(const QString &avatar) {
    m_avatar = avatar;
}

void VoiceInfo::setSprite(const QString &sprite) {
    m_sprite = sprite;
}

void VoiceInfo::resetCore() {
    m_name = "";
    m_author = "";
    m_avatar = "";
    m_sprite = "";
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

    QStringList lines;
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }

    QSettingSection section;
    section.fromLines(lines);
    QString *nameValue = section.valueOf(KEY_NAME_CHAR_NAME);
    if (nameValue) {
        m_name = *nameValue;
    }
    QString *avatarValue = section.valueOf(KEY_NAME_CHAR_IMAGE);
    if (avatarValue) {
        m_avatar = QDir::fromNativeSeparators(*avatarValue);
    }
    QString *authorValue = section.valueOf(KEY_NAME_CHAR_AUTHOR);
    if (authorValue) {
        m_author = *authorValue;
    }
    QString *spriteValue = section.valueOf(KEY_NAME_CHAR_FOREGROUND);
    if (spriteValue) {
        m_sprite = QDir::fromNativeSeparators(*spriteValue);
    }
    m_custom = section.unformattedLines();

    return true;
}

bool VoiceInfo::saveCharTxt() {
    QSettingSection section;
    if (!m_name.isEmpty()) {
        section.addPair(KEY_NAME_CHAR_NAME, m_name);
    }
    if (!m_avatar.isEmpty()) {
        section.addPair(KEY_NAME_CHAR_IMAGE, QDir::toNativeSeparators(m_avatar));
    }
    if (!m_author.isEmpty()) {
        section.addPair(KEY_NAME_CHAR_AUTHOR, m_author);
    }
    if (!m_sprite.isEmpty()) {
        section.addPair(KEY_NAME_CHAR_FOREGROUND, QDir::toNativeSeparators(m_sprite));
    }
    section.setUnformattedLines(m_custom);

    QStringList lines = section.toLines();

    QByteArray data;
    QTextStream out(&data);
    out.setCodec(m_codec);
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        out << *it << Qt::endl;
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
