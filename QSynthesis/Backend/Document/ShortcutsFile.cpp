#include "ShortcutsFile.h"
#include "QSActions.h"

Q_SINGLETON_DECLARE(ShortcutsFile)

ShortcutsFile *ShortcutsFile::defaultData = nullptr;

ShortcutsFile::ShortcutsFile() : BaseFile(Qs::Default) {
    reset();
}

ShortcutsFile::ShortcutsFile(const QString &filename) : BaseFile(Qs::Default) {
    setFilename(filename);
}

ShortcutsFile::~ShortcutsFile() {
}

void ShortcutsFile::setData(const ShortcutsFile &another) {
    commonShortcuts = another.commonShortcuts;
    projectShortcuts = another.projectShortcuts;
    voiceShortcuts = another.voiceShortcuts;
}

void ShortcutsFile::makeDefault() {
    setData(getDefault());
}

ShortcutsFile::ShortcutsFile(Qs::VariableSource source) {
    Q_ASSERT(source == Qs::Default);
    commonShortcuts = BaseActionList::commonDefaultShortcuts();
    projectShortcuts = TuningActionList::defaultShortcuts();
    voiceShortcuts = VoiceActionList::defaultShortcuts();
}

bool ShortcutsFile::loadCore(bool *valid) {
    QFile file(m_filename);
    QByteArray bytes;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    bytes = file.readAll();
    file.close();

    // Parse Json File
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseJsonErr);
    if (parseJsonErr.error != QJsonParseError::NoError) {
        return false;
    }
    QJsonObject obj = document.object();
    setData(fromJson(obj));
    return true;
}

bool ShortcutsFile::saveCore() {
    QJsonDocument doc;
    doc.setObject(toJson(*this));

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
    makeDefault();
}

QJsonObject ShortcutsFile::toJson(const ShortcutsFile &keys) {
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

ShortcutsFile ShortcutsFile::fromJson(const QJsonObject &obj) {
    ShortcutsFile data;
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
        return ShortcutsFile::getDefault();
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
        return ShortcutsFile::getDefault();
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
        return ShortcutsFile::getDefault();
    }

    if (!ShortcutsFile::checkNoConflict(data)) {
        return ShortcutsFile::getDefault();
    }
    return data;
}

void ShortcutsFile::createDefault() {
    Q_ASSERT(!defaultData);
    defaultData = new ShortcutsFile(Qs::Default);
}

ShortcutsFile ShortcutsFile::getDefault() {
    return *defaultData;
}

void ShortcutsFile::removeDefault() {
    Q_ASSERT(defaultData);
    delete defaultData;
    defaultData = nullptr;
}

bool ShortcutsFile::checkNoConflict(const ShortcutsFile &sd, QPair<int, int> *first,
                                    QPair<int, int> *second) {
    const QList<QKeySequence> &commonKeys = sd.commonShortcuts;

    QMap<QKeySequence, int> map;
    QMap<QKeySequence, int> map1;

    for (int i = 0; i < commonKeys.size(); ++i) {
        QKeySequence shortcut = commonKeys.at(i);
        auto it = map.find(shortcut);
        if (it != map.end()) {
            if (first) {
                first->first = 0;
                first->second = it.value();
            }
            if (second) {
                second->first = 0;
                second->second = i + 1;
            }
            return false;
        }
        if (!shortcut.toString().isEmpty()) {
            map.insert(shortcut, i + 1);
        }
    }

    const QList<QKeySequence> &projectKeys = sd.projectShortcuts;
    for (int i = 0; i < projectKeys.size(); ++i) {
        QKeySequence shortcut = projectKeys.at(i);
        auto it = map.find(shortcut);
        if (it != map.end()) {
            if (first) {
                first->first = 0;
                first->second = it.value();
            }
            if (second) {
                second->first = 1;
                second->second = i + 1;
            }
            return false;
        }
        auto it1 = map1.find(shortcut);
        if (it1 != map1.end()) {
            if (first) {
                first->first = 1;
                first->second = it1.value();
            }
            if (second) {
                second->first = 1;
                second->second = i + 1;
            }
            return false;
        }
        if (!shortcut.toString().isEmpty()) {
            map1.insert(shortcut, i + 1);
        }
    }
    map1.clear();

    const QList<QKeySequence> &voiceKeys = sd.voiceShortcuts;
    for (int i = 0; i < voiceKeys.size(); ++i) {
        QKeySequence shortcut = voiceKeys.at(i);
        auto it = map.find(shortcut);
        if (it != map.end()) {
            if (first) {
                first->first = 0;
                first->second = it.value();
            }
            if (second) {
                second->first = 2;
                second->second = i + 1;
            }
            return false;
        }
        auto it1 = map1.find(shortcut);
        if (it1 != map1.end()) {
            if (first) {
                first->first = 2;
                first->second = it1.value();
            }
            if (second) {
                second->first = 2;
                second->second = i + 1;
            }
            return false;
        }
        if (!shortcut.toString().isEmpty()) {
            map1.insert(shortcut, i + 1);
        }
    }
    return true;
}
