#ifndef WELCOMETAB_H
#define WELCOMETAB_H

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QStyledItemDelegate>

#include "../Central/CentralTab.h"
#include "Actions/WelcomeActionList.h"
#include "Containers/LinearScrollArea.h"
#include "FileListWidgetItem.h"
#include "WelcomeTabContent.h"

#include "QUtils.h"

// Welcoming Tab Class
class WelcomeTab : public CentralTab {
    Q_OBJECT
public:
    explicit WelcomeTab(CentralTabWidget *parent = nullptr);
    ~WelcomeTab();

    WelcomeActionList *tabActions;

public:
    void awake() override;
    void sleep() override;

    void enter() override;
    void leave() override;

    void setFixedname(const QString &value) override;

protected:
    void updateMenuRoot() override;
    void updateStatusRoot() override; // Update status when switch to current tab

    void updateTabName() override;

private:
    QGridLayout *mainLayout;
    LinearScrollArea *mainScroll; // Main Container
    WelcomeTabContent *mainWidget;
};

#endif // WELCOMETAB_H
