#ifndef KEYTABLETAB_H
#define KEYTABLETAB_H

#include <QHeaderView>
#include <QTableWidget>
#include <QVBoxLayout>

#include "Tabs/BaseTab.h"

class KeyTableTab : public BaseTab {
public:
    explicit KeyTableTab(TabWidget *parent = nullptr);
    virtual ~KeyTableTab();

private:
    QVBoxLayout *mainLayout;
    QTableWidget *table;
};

#endif // KEYTABLETAB_H
