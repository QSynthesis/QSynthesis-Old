#include "ShortcutsFile.h"

ShortcutsFile::ShortcutsFile(QObject *parent) : FileManager(parent) {
    reset();
}

ShortcutsFile::ShortcutsFile(const QString &filename, QObject *parent) : FileManager(parent) {
    setFilename(filename);
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
    m_data = ShortcutsData();
}

void ShortcutsFile::setData(const ShortcutsData &data) {
    m_data = data;
}

ShortcutsData ShortcutsFile::data() const {
    return m_data;
}

QJsonObject ShortcutsFile::toJson(const ShortcutsData &keys) {
    const ShortcutsData defaultKeys;
    QJsonObject data, obj;
    QJsonArray arr;

    for (int i = ShortcutsData::idStart(); i < ShortcutsData::idEnd(); ++i) {
        obj = toKeyObject(i, keys.keyForId(i), defaultKeys.keyForId(i));
        arr.append(obj);
    }

    data["commands"] = arr;
    return data;
}

ShortcutsData ShortcutsFile::fromJson(const QJsonObject &obj) {
    ShortcutsData keys;
    QJsonArray arr;

    QJsonValue valCmds = obj.value("commands");
    if (valCmds.isArray()) {
        arr = valCmds.toArray();
    } else {
        return keys;
    }

    for (auto it = arr.begin(); it != arr.end(); ++it) {
        QJsonValue val = *it;
        if (!val.isObject()) {
            continue;
        }
        QJsonObject obj = val.toObject();
        int id = obj.value("id").toInt();
        QString key = obj.value("key").toString();

        keys.setKeyForId(id, QKeySequence(key));
    }

    return keys;
}

QJsonObject ShortcutsFile::toKeyObject(int id, const QKeySequence &key, const QKeySequence &def) {
    QJsonObject obj;

    obj["id"] = id;
    obj["key"] = key.toString();
    obj["default"] = key == def;

    return obj;
}
