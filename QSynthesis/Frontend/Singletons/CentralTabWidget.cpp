#include "CentralTabWidget.h"
#include "Controls/Buttons/IconButton.h"
#include "Controls/Buttons/VectorButton.h"

#include <QPushButton>

Q_SINGLETON_DECLARE(CentralTabWidget)

// CentralTabWidget::CentralTabWidget(QWidget *parent) : TabWidget(parent) {
//    createCasePrivate();

//    selector = new ComboSelector(this);
//    selector->setMinimumSize(600, 400);
//    selector->hide();
//}

// CentralTabWidget::~CentralTabWidget() {
//}

// void CentralTabWidget::addTabCore(int index) {
//    VectorButton *btn = new VectorButton(true, QSizeF(3, 3));
//    btn->setProperty("type", "tab-close");
//    btn->setProperty("highlight", currentIndex() == index);

//    btn->setIcons(":/images/close-line.svg");

//    QTabBar *bar = tabBar();
//    CentralTab *tab = tabAt(index);

//    closeBtns.insert(tab, btn);

//    bar->setTabButton(index, QTabBar::LeftSide, nullptr);
//    bar->setTabButton(index, QTabBar::RightSide, btn);

//    connect(btn, &VectorButton::clicked, this, [=]() { emit tabCloseRequested(indexOf(tab)); });

//    btn->setFixedSize(18, 18);
//}

// void CentralTabWidget::removeTabCore(int index) {
//    closeBtns.remove(tabAt(index));
//}

// void CentralTabWidget::tabIndexChangeCore(int index, bool changed) {
//    CentralTab *cur = currentTab();
//    CentralTab *prev = previousTab();

//    if (cur) {
//        auto it = closeBtns.find(cur);
//        if (it != closeBtns.end()) {
//            VectorButton *btn = it.value();
//            btn->setProperty("highlight", true);
//            style()->polish(btn);
//        }
//    }
//    if (prev) {
//        auto it = closeBtns.find(prev);
//        if (it != closeBtns.end()) {
//            VectorButton *btn = it.value();
//            btn->setProperty("highlight", false);
//            style()->polish(btn);
//        }
//    }
//}

// void CentralTabWidget::adjustSelector() {
//    if (selector->isVisible()) {
//        selector->adjustSize();
//        selector->resize(width() / 2, height() / 2);
//        selector->move((width() - selector->width()) / 2, 0);
//    }
//}

// void CentralTabWidget::resizeEvent(QResizeEvent *event) {
//    if (selector->isVisible()) {
//        adjustSelector();
//    }
//    TabWidget::resizeEvent(event);
//}

CentralTabWidget::CentralTabWidget(QWidget *parent) : TabWidget(parent) {
    createCasePrivate();

    selector = new ComboSelector(this);
    selector->setMinimumSize(600, 400);
    selector->hide();
}

CentralTabWidget::~CentralTabWidget() {
}

void CentralTabWidget::addTabCore(int index) {
    IconButton *btn = new IconButton(QSizeF(6, 6));
    btn->setProperty("type", "tab-close");
    btn->setProperty("highlight", currentIndex() == index);

    btn->setIcon(":/images/close-line.svg");

    QTabBar *bar = tabBar();
    CentralTab *tab = tabAt(index);

    closeBtns.insert(tab, btn);

    bar->setTabButton(index, QTabBar::LeftSide, nullptr);
    bar->setTabButton(index, QTabBar::RightSide, btn);

    connect(btn, &IconButton::clicked, this, [=]() { emit tabCloseRequested(indexOf(tab)); });

    btn->setFixedSize(24, 24);
}

void CentralTabWidget::removeTabCore(int index) {
    closeBtns.remove(tabAt(index));
}

void CentralTabWidget::tabIndexChangeCore(int index, bool changed) {
    CentralTab *cur = currentTab();
    CentralTab *prev = previousTab();

    if (cur) {
        auto it = closeBtns.find(cur);
        if (it != closeBtns.end()) {
            IconButton *btn = it.value();
            btn->setProperty("highlight", true);
            style()->polish(btn);
        }
    }
    if (prev) {
        auto it = closeBtns.find(prev);
        if (it != closeBtns.end()) {
            IconButton *btn = it.value();
            btn->setProperty("highlight", false);
            style()->polish(btn);
        }
    }
}

void CentralTabWidget::adjustSelector() {
    if (selector->isVisible()) {
        selector->adjustSize();
        selector->resize(width() / 2, height() / 2);
        selector->move((width() - selector->width()) / 2, 0);
    }
}

void CentralTabWidget::resizeEvent(QResizeEvent *event) {
    if (selector->isVisible()) {
        adjustSelector();
    }
    TabWidget::resizeEvent(event);
}
