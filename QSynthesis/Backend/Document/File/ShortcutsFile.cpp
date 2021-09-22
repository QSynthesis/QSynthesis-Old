#include "ShortcutsFile.h"

ShortcutsFile::ShortcutsFile(QObject *parent) : FileManager(parent) {
    reset();
}

ShortcutsFile::ShortcutsFile(const QString &filename, QObject *parent) : FileManager(parent) {
    setFilename(filename);
}

ShortcutsFile::~ShortcutsFile() {
}

void ShortcutsFile::setData(const ShortcutsData &data) {
    m_data = data;
}

ShortcutsData ShortcutsFile::data() const {
    return m_data;
}

bool ShortcutsFile::loadCore(bool *valid) {
    QFile file(m_filename);
    QByteArray bytes;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    bytes = file.readAll();
    file.close();

    if (valid) {
        *valid = true;
    }

    // Parse Json File
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseJsonErr);
    if (parseJsonErr.error != QJsonParseError::NoError) {
        // QMessageBox::about(NULL, ErrorTitle, "Invalid format!");
        if (valid) {
            *valid = false;
        }
        return true;
    }
    QJsonObject obj = document.object();
    m_data = fromJson(obj);
    return true;
}

bool ShortcutsFile::saveCore() {
    QJsonDocument doc;
    doc.setObject(toJson(m_data));

    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    file.seek(0);
    file.write(doc.toJson());
    file.flush();

    return true;
}

void ShortcutsFile::resetCore() {
    m_data = ShortcutsData::getDefault();
}

QJsonObject ShortcutsFile::toJson(const ShortcutsData &keys) {
    const QList<QKeySequence> &commonKeys = keys.commonShortcuts;
    const QList<QKeySequence> &projectKeys = keys.projectShortcuts;
    const QList<QKeySequence> &voiceKeys = keys.voiceShortcuts;

    QJsonObject obj;

    QJsonArray commonArr;
    for (auto it = commonKeys.begin(); it != commonKeys.end(); ++it) {
        commonArr.append(it->toString());
    }

    QJsonArray projectArr;
    for (auto it = projectKeys.begin(); it != projectKeys.end(); ++it) {
        projectArr.append(it->toString());
    }

    QJsonArray voiceArr;
    for (auto it = voiceKeys.begin(); it != voiceKeys.end(); ++it) {
        voiceArr.append(it->toString());
    }

    obj.insert("common", commonArr);
    obj.insert("project", projectArr);
    obj.insert("voice", voiceArr);

    return obj;
}

ShortcutsData ShortcutsFile::fromJson(const QJsonObject &obj) {
    ShortcutsData data = ShortcutsData::getDefault();

    QJsonValue valCommon = obj.value("common");
    if (valCommon.isArray()) {
        QList<QKeySequence> commonKeys;
        QJsonArray commonArr = valCommon.toArray();
        for (auto it = commonArr.begin(); it != commonArr.end(); ++it) {
            if (it->isString()) {
                QKeySequence key((it->toString()));
                commonKeys.append(key);
            }
        }
        if (commonKeys.size() == data.commonShortcuts.size()) {
            data.commonShortcuts = commonKeys;
        }
    } else {
        return ShortcutsData::getDefault();
    }

    QJsonValue valProject = obj.value("project");
    if (valProject.isArray()) {
        QList<QKeySequence> projectKeys;
        QJsonArray projectArr = valProject.toArray();
        for (auto it = projectArr.begin(); it != projectArr.end(); ++it) {
            if (it->isString()) {
                QKeySequence key((it->toString()));
                projectKeys.append(key);
            }
        }
        if (projectKeys.size() == data.projectShortcuts.size()) {
            data.projectShortcuts = projectKeys;
        }
    } else {
        return ShortcutsData::getDefault();
    }

    QJsonValue valVoice = obj.value("voice");
    if (valVoice.isArray()) {
        QList<QKeySequence> voiceKeys;
        QJsonArray voiceArr = valVoice.toArray();
        for (auto it = voiceArr.begin(); it != voiceArr.end(); ++it) {
            if (it->isString()) {
                QKeySequence key((it->toString()));
                voiceKeys.append(key);
            }
        }
        if (voiceKeys.size() == data.voiceShortcuts.size()) {
            data.voiceShortcuts = voiceKeys;
        }
    } else {
        return ShortcutsData::getDefault();
    }

    if (!ShortcutsData::checkNoConflict(data)) {
        return ShortcutsData::getDefault();
    }
    return data;
}
