#ifndef CENTRALTABWIDGET_H
#define CENTRALTABWIDGET_H

#include "TabWidget.h"

class VectorButton;

class CentralTabWidget : public TabWidget {
public:
    explicit CentralTabWidget(QWidget *parent = nullptr);
    ~CentralTabWidget();

private:
    void addTabCore(int index) override;
    void removeTabCore(int index) override;

    QHash<QWidget *, VectorButton *> closeBtns;
};

#endif // CENTRALTABWIDGET_H
