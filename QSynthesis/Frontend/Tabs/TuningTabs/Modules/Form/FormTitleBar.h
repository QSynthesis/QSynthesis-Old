#ifndef FORMTITLEBAR_H
#define FORMTITLEBAR_H

#include <QObject>
#include <QWidget>

#include "Templates/VectorButton.h"

class BaseForm;

class FormTitleBar : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QColor topColor READ topColor WRITE setTopColor NOTIFY colorChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY colorChanged)

public:
    explicit FormTitleBar(BaseForm *parent = nullptr);
    explicit FormTitleBar(int h, BaseForm *parent = nullptr);

    int contentHeight() const;
    void setContentHeight(int h);

    int top() const;
    void setTop(double t);
    void setTopVisible(bool value);

    void addItem(QWidget *item, bool rightToLeft = false, bool hidden = true, bool showen = true);
    void removeItem(QWidget *item);
    void hideItems();
    void showItems();
    void setItemsVisible(bool value);

public:
    QColor topColor() const;
    void setTopColor(const QColor &value);

    QColor fillColor() const;
    void setFillColor(const QColor &value);

signals:
    void colorChanged();

protected:
    struct titleBarItem {
        QWidget *item;
        bool hidden;
        bool showen;

        titleBarItem(QWidget *w, bool h, bool s) : item(w), hidden(h), showen(s) {
        }
    };

    BaseForm *parentForm;

    int m_height;
    double m_top;

    QList<titleBarItem> itemsList;
    bool topVisible;

    QColor m_topColor;
    QColor m_fillColor;

    QHBoxLayout *itemsLayout;
    QLayoutItem *stretch;

private:
    void paintEvent(QPaintEvent *event) override;

    void initializeComponents(int h, int t);

signals:
};

#endif // FORMTITLEBAR_H
