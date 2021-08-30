#ifndef WELCOMEACTIONLIST_H
#define WELCOMEACTIONLIST_H

#include "BaseActionList.h"

class WelcomeActionList : public BaseActionList {
    Q_OBJECT
public:
    WelcomeActionList(QObject *parent = nullptr);
    ~WelcomeActionList();

public:
    void setNaturalStatus() override;
};

#endif // WELCOMEACTIONLIST_H
