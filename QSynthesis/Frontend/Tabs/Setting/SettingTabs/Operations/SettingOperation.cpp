#include "SettingOperation.h"

SettingOperation::SettingOperation(const SettingType t, const QString &k, const QJsonValue &from,
                                   const QJsonValue &to, SettingOperation *n)
    : type(t), key(k), fromVal(from), toVal(to), next(n) {
}

QString settingTypeToString(const SettingType type) {
    switch (type) {
    case Edit:
        return "Edit";
    case KeyBoard:
        return "KeyBoard";
    case Mouse:
        return "Mouse";
    case Render:
        return "Render";
    case Cache:
        return "Cache";
    default:
        return QString();
    }
}
