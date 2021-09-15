#ifndef CENTRALTABWIDGET_H
#define CENTRALTABWIDGET_H

#include "ComboSelector.h"
#include "TabWidget.h"

class VectorButton;

class CentralTabWidget : public TabWidget {
    Q_OBJECT
    Q_SINGLETON(CentralTabWidget)

public:
    explicit CentralTabWidget(QWidget *parent = nullptr);
    ~CentralTabWidget();

private:
    void addTabCore(int index) override;
    void removeTabCore(int index) override;

    QHash<QWidget *, VectorButton *> closeBtns;

private:
    ComboSelector *selector;

    void adjustSelector();

    void handleSelectorIndexChanged(int index);
    void handleSelectorActivated(int index);
    void handleSelectorAbandoned();

public:
    int useSelector(const QStringList &items, int current, void previewFuction(int));

private:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CENTRALTABWIDGET_H
