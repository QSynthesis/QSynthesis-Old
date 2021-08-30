#ifndef COMBOCONTROL_H
#define COMBOCONTROL_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include "QUtils.h"

class ComboControl : public QWidget {
    Q_OBJECT
public:
    explicit ComboControl(Qt::Orientation orient, QWidget *parent = NULL);
    explicit ComboControl(Qt::Orientation orient, QString text, QWidget *parent = NULL);
    explicit ComboControl(Qt::Orientation orient, QString text, const QStringList &values,
                          QWidget *parent = NULL);

    void setCaption(QString caption);
    QString caption() const;

    void setProportion(int a, int b);
    void setMargin(int n);

    void setUnmodified(bool value);
    bool isUnmodified();

    QComboBox *Combo() const;

    Qt::Orientation orientation() const;

private:
    QString value;
    void InitComboControl(QString text, const QStringList &values);
    void onModifyAction();

    QComboBox *pCombo;
    QLabel *pLabel;

    QLayout *pLayout;

    bool bUnmodified;

    Qt::Orientation orient;
};

#endif // COMBOCONTROL_H
