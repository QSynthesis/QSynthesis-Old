#include "CentralTabWidget.h"
#include "../TuningTabs/Modules/Buttons/VectorButton.h"

#include <QPushButton>

CentralTabWidget::CentralTabWidget(QWidget *parent) : TabWidget(parent) {
}

CentralTabWidget::~CentralTabWidget() {
}

void CentralTabWidget::addTabCore(int index) {
    VectorButton *btn = new VectorButton(true, QSizeF(3, 3));
    btn->setIcons(":/images/close-line.svg");

    QTabBar *bar = tabBar();
    BaseTab *tab = tabAt(index);

    closeBtns.insert(tab, btn);

    bar->setTabButton(index, QTabBar::LeftSide, nullptr);
    bar->setTabButton(index, QTabBar::RightSide, btn);

    connect(btn, &VectorButton::clicked, this, [=]() { emit tabCloseRequested(indexOf(tab)); });

    btn->setFixedSize(18, 18);
}

void CentralTabWidget::removeTabCore(int index) {
    closeBtns.remove(tabAt(index));
}
