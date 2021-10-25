#include "QUtauStrCore.h"
#include "Common/QUtauStd.h"

using namespace UtaFilenames;
using namespace Utau;

#include <QDir>

QString fromUSTVoiceDir(const QString &filePath, const QString &appPath) {
    QString path = QDir::fromNativeSeparators(filePath);
    QString voice = appPath + SLASH + DIR_NAME_VOICE + SLASH;

    int index = filePath.indexOf(DIR_VOICE_BASE);
    if (index >= 0) {
        path.replace(DIR_VOICE_BASE, voice);
    } else if (QFileInfo(path).isRelative()) {
        path = appPath + SLASH + path;
    }

    return path;
}

QString toUSTVoiceDir(const QString &filePath, const QString &appPath) {
    QString path = filePath;
    QString voice = appPath + SLASH + DIR_NAME_VOICE + SLASH;

    if (path.startsWith(voice)) {
        path = DIR_VOICE_BASE + filePath.mid(voice.size());
    }

    path = QDir::toNativeSeparators(filePath);
    return path;
}

QString fromUSTToolsDir(const QString &filePath, const QString &appPath) {
    QString path = QDir::fromNativeSeparators(filePath);
    if (QFileInfo(path).isRelative()) {
        path = appPath + SLASH + path;
    }
    return path;
}

QString toUSTToolsDir(const QString &filePath, const QString &appPath) {
    QString path = filePath;
    QString app = appPath + SLASH;
    if (filePath.startsWith(app)) {
        path = path.mid(app.size());
    }
    path = QDir::toNativeSeparators(path);
    return path;
}
