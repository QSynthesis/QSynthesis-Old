#ifndef BASEFORM_H
#define BASEFORM_H

#include <QWidget>

#include "../Modules/Form/FormTitleBar.h"

class BaseForm : public QWidget {
    Q_OBJECT
public:
    explicit BaseForm(QWidget *parent = nullptr);
    explicit BaseForm(QWidget *w, FormTitleBar *bar, QWidget *parent = nullptr);

    bool unfolded() const;
    void setUnfolded(bool value);
    void reverseFold();

    QWidget *widget() const;
    void setWidget(QWidget *w);
    void setDefaultWidget();

    FormTitleBar *titleBar() const;
    void setTitleBar(FormTitleBar *bar);
    void setDefaultTitleBar();

protected:
    QVBoxLayout *mainLayout;

    FormTitleBar *m_titleBar;
    QWidget *m_widget;

    bool m_unfolded;

private:
    void init();

signals:
    void visibilityChanged(bool vi);
    void heightChanged(int h);
};

#endif // BASEFORM_H
