#ifndef SETTINGOPERATION_H
#define SETTINGOPERATION_H

#include <QJsonDocument>
#include <QString>

#include "Operation.h"

enum SettingType { Error, Edit, KeyBoard, Mouse, Render, Cache };

QString settingTypeToString(const SettingType type);

class SettingOperation : public Operation {
public:
    SettingOperation(const SettingType t, const QString &k, const QJsonValue &from,
                     const QJsonValue &to, SettingOperation *n = nullptr);

    SettingType type;
    QString key;
    QJsonValue fromVal;
    QJsonValue toVal;
    SettingOperation *next;
};

#endif // SETTINGOPERATION_H
