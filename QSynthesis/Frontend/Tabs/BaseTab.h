#ifndef BASETAB_H
#define BASETAB_H

#include <QDebug>
#include <QObject>
#include <QTabWidget>
#include <QWidget>

#include "Global/Methods.h"

class MainWindow;
class TabWidget;

class BaseTab : public QWidget {
    Q_OBJECT

public:
    explicit BaseTab(TabWidget *parent);
    virtual ~BaseTab();

    virtual QString tabName() const; // Get the title of tab

    TabWidget *parentTabWidget() const;

    inline MainWindow *root() {
        return Root(this);
    }

protected:
    TabWidget *m_parent;
    QString m_tabName;

    virtual void setTabName(const QString &value); // Set the title of tab
    virtual void updateTabName();

signals:
    void tabNameChanged(const QString &name);
};

#endif // BASETAB_H
