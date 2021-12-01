#include "VoiceInfo.h"
#include "QSettingFile.h"
#include "QUtauStrCore.h"
#include "QUtauStrExtern.h"
#include "SystemApis.h"

#include <QDir>
#include <QFile>
#include <QTextStream>

using namespace Utau;

Q_CHARSET_DECLARE(VoiceInfo)

VoiceInfo::VoiceInfo() : BaseDirInfo(Qs::Default) {
    init();
    reset();
}

VoiceInfo::VoiceInfo(const QString &dirname) : BaseDirInfo(Qs::Default) {
    init();
    setDirname(dirname);
}

VoiceInfo::~VoiceInfo() {
}

VoiceInfo::VoiceInfo(Qs::VariableSource source) {
    init();
}

void VoiceInfo::init() {
    m_codec = defaultCodec;
}

bool VoiceInfo::loadCore(bool *valid) {
    QFile file(filename());
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    data = file.readAll();
    file.close();

    QTextCodec *codec = GetUtfCodec(data);
    QTextStream in(&data);
    if (codec) {
        m_codec = codec;
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

bool VoiceInfo::saveCore() {
    QFile file(filename());
    QByteArray data;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

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

    QTextStream out(&data);
    out.setCodec(m_codec);
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        out << *it << Qt::endl;
    }

    file.write(data);
    file.close();
    return true;
}

QString VoiceInfo::name() const {
    return m_name;
}

QString VoiceInfo::title() const {
    if (m_name.isEmpty()) {
        return QFileInfo(dirname()).fileName();
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

QString VoiceInfo::infoFilename() const {
    return FILE_NAME_CHAR_TEXT;
}
