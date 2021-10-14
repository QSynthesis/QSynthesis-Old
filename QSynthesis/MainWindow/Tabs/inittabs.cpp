#include "QSTabs.h"
#include "mainwindow.h"

void MainWindow::initTabs() {
    tabs = new CentralTabWidget(this);
    tabs->setProperty("type", "central");

    tabs->setMovable(true);      // Set the tab movable
    tabs->setTabsClosable(true); // Set the tab closable

    tabs->tabBar()->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);

    setCentralWidget(tabs);

    connect(tabs, &CentralTabWidget::titleChanged, this, &MainWindow::handleTabNameChanged);
    connect(tabs, &CentralTabWidget::tabCloseRequested, this, &MainWindow::handleTabCloseRequent);
    connect(tabs, &CentralTabWidget::realIndexChanged, this, &MainWindow::handleTabIndexChanged);
    connect(tabs, &CentralTabWidget::tabPressed, this, &MainWindow::handleTabPressed);
}
