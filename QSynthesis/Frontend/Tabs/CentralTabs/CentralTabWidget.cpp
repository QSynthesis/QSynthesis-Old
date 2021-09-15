#include "CentralTabWidget.h"
#include "Templates/VectorButton.h"

#include <QPushButton>

Q_SINGLETON_DECLARE(CentralTabWidget)

CentralTabWidget::CentralTabWidget(QWidget *parent) : TabWidget(parent) {
    createCasePrivate();

    selector = new ComboSelector(this);
    selector->setMinimumSize(600, 400);
    selector->hide();
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

void CentralTabWidget::adjustSelector() {
    if (selector->isVisible()) {
        selector->adjustSize();
        selector->resize(width() / 2, height() / 2);
        selector->move((width() - selector->width()) / 2, 0);
    }
}

void CentralTabWidget::handleSelectorIndexChanged(int index) {
}

void CentralTabWidget::handleSelectorActivated(int index) {
}

void CentralTabWidget::handleSelectorAbandoned() {
}

int CentralTabWidget::useSelector(const QStringList &items, int current, void previewFuction(int)) {
    selector->setItems(items);
    selector->setCurrentIndex(current);

    int result = -1;
    QEventLoop loop;

    connect(selector, &ComboSelector::currentIndexChanged, this,
            [&previewFuction](int index) mutable { previewFuction(index); });
    connect(selector, &ComboSelector::abandoned, this, [&loop]() mutable { loop.quit(); });
    connect(selector, &ComboSelector::activated, this, [&result, &loop](int index) mutable {
        result = index;
        loop.quit();
    });
    selector->show();

    adjustSelector();
    loop.exec();

    selector->disconnect();
    selector->hide();

    return result;
}

void CentralTabWidget::resizeEvent(QResizeEvent *event) {
    if (selector->isVisible()) {
        adjustSelector();
    }
    TabWidget::resizeEvent(event);
}
