#ifndef BASETAB_H
#define BASETAB_H

#include <QDebug>
#include <QObject>
#include <QTabWidget>

#include "Global/Methods.h"
#include "MoreWidget.h"

class MainWindow;
class TabWidget;

class BaseTab : public MoreWidget {
    Q_OBJECT

public:
    explicit BaseTab(TabWidget *parent = nullptr);
    virtual ~BaseTab();

    virtual void enter();
    virtual void leave();

    virtual QString tabName() const; // Get the title of tab

    TabWidget *tabWidget() const;

    bool active() const;

protected:
    virtual void setTabName(const QString &value); // Set the title of tab
    virtual void updateTabName();

private:
    TabWidget *m_parent;
    QString m_tabName;

    bool m_active;

signals:
    void tabNameChanged(const QString &name);
};

#endif // BASETAB_H
