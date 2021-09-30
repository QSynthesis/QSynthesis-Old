#ifndef CENTRALTABWIDGET_H
#define CENTRALTABWIDGET_H

#include "ComboSelector.h"
#include "TabWidget.h"
#include "Tabs/CentralTab.h"

class VectorButton;

#define qMainTabs CentralTabWidget::instance()

class CentralTabWidget : public TabWidget {
    Q_OBJECT
    Q_SINGLETON(CentralTabWidget)

public:
    explicit CentralTabWidget(QWidget *parent = nullptr);
    ~CentralTabWidget();

    int addTab(CentralTab *tab, const QString &label);
    int addTab(CentralTab *tab, const QIcon &icon, const QString &label);

    int insertTab(int index, CentralTab *tab, const QString &label);
    int insertTab(int index, CentralTab *tab, const QIcon &icon, const QString &label);

    CentralTab *currentWidget() const;
    CentralTab *tabAt(int index) const;
    int indexOf(CentralTab *tab) const;

    void setCornerWidget(CentralTab *w, Qt::Corner corner = Qt::TopRightCorner);
    CentralTab *cornerWidget(Qt::Corner corner = Qt::TopRightCorner) const;

    void setCurrentWidget(CentralTab *tab);

    void removeTab(int index);
    void removeTab(CentralTab *tab);

    CentralTab *currentTab() const;
    CentralTab *previousTab() const;

public:
    int useSelector(const QStringList &items, const QString &clues, int current,
                    void previewFuction(int) = nullptr);

private:
    void addTabCore(int index) override;
    void removeTabCore(int index) override;

    void tabIndexChangeCore(int index, bool changed) override;

    QHash<CentralTab *, VectorButton *> closeBtns;

private:
    ComboSelector *selector;

    void adjustSelector();

private:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CENTRALTABWIDGET_H
