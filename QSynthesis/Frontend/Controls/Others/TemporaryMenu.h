#ifndef TEMPORARYMENU_H
#define TEMPORARYMENU_H

#include <QAction>
#include <QMenu>

#include "Types.h"

class TemporaryMenu : public QMenu {
    Q_OBJECT
public:
    explicit TemporaryMenu(QWidget *parent = nullptr);
    explicit TemporaryMenu(const QStringList &list,QWidget *parent = nullptr);
    ~TemporaryMenu();

    int start();
    int start(QPoint pos);

    QStringList texts() const;
    void setTexts(const QStringList &texts);

    void setCheckedAt(int index, bool checked);
    void setEnabledAt(int index, bool enabled);
    void setVisibleAt(int index, bool visible);

    bool checkable() const;
    void setCheckable(bool checkable);

    void clearContents();

private:
    QStringList m_texts;

    QMap<int, bool> m_checks;
    QMap<int, bool> m_enables;
    QMap<int, bool> m_visibilities;

    bool m_checkable;

    void prepare();
};

#endif // TEMPORARYMENU_H
