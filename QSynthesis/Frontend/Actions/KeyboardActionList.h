#ifndef KEYBOARDACTIONLIST_H
#define KEYBOARDACTIONLIST_H

#include "BaseActionList.h"

class KeyboardActionList : public BaseActionList {
    Q_OBJECT
    Q_SINGLETON(KeyboardActionList)
public:
    KeyboardActionList(QObject *parent = nullptr);
    ~KeyboardActionList();

public:
    void setNaturalStatus() override;
};

#endif // KEYBOARDACTIONLIST_H
