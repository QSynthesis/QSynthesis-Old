#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QPointer>
#include <QTabBar>
#include <QTabWidget>

#include "Tabs/BaseTab.h"

// A container of tab widget
class TabWidget : public QTabWidget {
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = nullptr);
    virtual ~TabWidget();

    int addTab(BaseTab *tab, const QString &label);
    int addTab(BaseTab *tab, const QIcon &icon, const QString &label);

    int insertTab(int index, BaseTab *tab, const QString &label);
    int insertTab(int index, BaseTab *tab, const QIcon &icon, const QString &label);

    BaseTab *currentWidget() const;
    BaseTab *tabAt(int index) const;
    int indexOf(BaseTab *tab) const;

    void setCornerWidget(BaseTab *w, Qt::Corner corner = Qt::TopRightCorner);
    BaseTab *cornerWidget(Qt::Corner corner = Qt::TopRightCorner) const;

    void setCurrentWidget(BaseTab *tab);

    void setTabTitle(int index, const QString &title);
    QString currentTitle() const;

    void removeTab(int index);
    void removeTab(BaseTab *tab);

    BaseTab *currentTab() const;
    BaseTab *previousTab() const;

protected:
    virtual void addTabCore(int index);
    virtual void removeTabCore(int index);

    virtual void tabIndexChangeCore(int index, bool changed);

private:
    QPointer<BaseTab> m_previousTab, m_currentTab;

    void handleTabIndexChanged(int index);
    void handleTabNameChanged(const QString &newName);

private:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void titleChanged(int index, const QString &title);
    void realIndexChanged(int index);

    void tabPressed(int index, Qt::MouseButton button);
    void tabReleased(int index, Qt::MouseButton button);
};

#endif // TABWIDGET_H
