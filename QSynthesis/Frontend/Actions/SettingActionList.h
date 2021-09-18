#ifndef SETTINGACTIONLIST_H
#define SETTINGACTIONLIST_H

#include "BaseActionList.h"

class SettingActionList : public BaseActionList {
    Q_OBJECT
    Q_SINGLETON(SettingActionList)
public:
    SettingActionList(QObject *parent = nullptr);
    ~SettingActionList();

public:
    void setNaturalStatus() override;
};

#endif // SETTINGACTIONLIST_H
