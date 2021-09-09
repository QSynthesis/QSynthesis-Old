#include "WelcomeTab.h"
#include "mainwindow.h"

WelcomeTab::WelcomeTab(TabWidget *parent) : CentralTab(parent) {
    m_type = Qs::Welcome;

    // 新建主容器
    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    // 新建滚动区域并添加到容器中
    mainScroll = new LinearScrollArea(Qt::Vertical);
    mainScroll->setFrameStyle(QFrame::NoFrame);
    mainLayout->addWidget(mainScroll);

    // 新建内容窗
    mainWidget = new WelcomeTabContent(this, mainScroll);
    mainScroll->setWidget(mainWidget);
}

WelcomeTab::~WelcomeTab() {
}

void WelcomeTab::awake() {
    CentralTab::awake();
}

void WelcomeTab::sleep() {
    CentralTab::sleep();
}

void WelcomeTab::enter() {
    CentralTab::enter();
}

void WelcomeTab::leave() {
    CentralTab::leave();
}

void WelcomeTab::setFixedname(const QString &value) {
    CentralTab::setFixedname(value);
    updateTabName();
}

void WelcomeTab::updateTabName() {
    setTabName(m_fixedname);
}

void WelcomeTab::updateMenuRoot() {
    tabActions->setNaturalStatus();
}

void WelcomeTab::updateStatusRoot() {
    mainWidget->refresh();
}
