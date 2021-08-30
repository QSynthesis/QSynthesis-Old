#ifndef TEMPORARYMENU_H
#define TEMPORARYMENU_H

#include <QAction>
#include <QMenu>

class TemporaryMenu : public QMenu {
    Q_OBJECT
public:
    explicit TemporaryMenu(QWidget *parent = nullptr);
    explicit TemporaryMenu(const QStringList &list, QWidget *parent = nullptr);
    ~TemporaryMenu();

    int start();
    int start(QPoint pos);

    QStringList texts() const;
    void setTexts(const QStringList &texts);
    void clearTexts();

private:
    QStringList m_texts;

    void prepare();
};

#endif // TEMPORARYMENU_H
