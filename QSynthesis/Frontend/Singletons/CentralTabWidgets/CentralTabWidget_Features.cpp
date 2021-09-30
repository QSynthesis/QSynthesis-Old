#include "../CentralTabWidget.h"

int CentralTabWidget::useSelector(const QStringList &items, const QString &clues, int current,
                                  void previewFuction(int)) {
    selector->setEditText("");
    selector->setItems(items);
    selector->setClues(clues);
    if (current >= 0 && current < items.size()) {
        selector->setCurrentIndex(current);
    }

    int result = -1;
    QEventLoop loop;

    connect(selector, &ComboSelector::currentIndexChanged, this,
            [&previewFuction](int index) mutable {
                if (previewFuction) {
                    previewFuction(index);
                }
            });
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
