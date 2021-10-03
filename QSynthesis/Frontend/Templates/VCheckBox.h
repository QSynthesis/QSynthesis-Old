#ifndef VCHECKBOX_H
#define VCHECKBOX_H

#include <QCheckBox>
#include <QHBoxLayout>

#include "Controls/SwitchButton.h"

class VCheckBox : public QAbstractButton {
    Q_OBJECT
public:
    explicit VCheckBox(QWidget *parent = nullptr);
    explicit VCheckBox(QString text, QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *) override;
};

#endif // VCHECKBOX_H
