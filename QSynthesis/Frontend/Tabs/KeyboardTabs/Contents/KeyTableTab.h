#ifndef KEYTABLETAB_H
#define KEYTABLETAB_H

#include <QHeaderView>
#include <QTableWidget>
#include <QVBoxLayout>

#include "Tabs/BaseTab.h"

class KeyTableTab : public BaseTab {
    Q_OBJECT
public:
    explicit KeyTableTab(TabWidget *parent = nullptr);
    virtual ~KeyTableTab();

    void addActionData(QAction *action);

private:
    QVBoxLayout *mainLayout;
    QTableWidget *table;
};

#endif // KEYTABLETAB_H
