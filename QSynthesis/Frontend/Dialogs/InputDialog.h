#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QValidator>

#include "../Controls/CustomControls.h"
#include "BaseDialog.h"
#include "QUtils.h"

class InputDialog : public BaseDialog {
    Q_OBJECT
public:
    explicit InputDialog(QString title, QString caption, double &value, QValidator *validator,
                         QWidget *parent = nullptr);
    ~InputDialog();

    int exec() override;

private:
    double &orgValue;

    QString m_title, m_caption;
    QValidator *m_validator;

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    QPushButton *btnCancel, *btnOK;
    LineControl *lcInput;

    void init();

    void onOKClicked();
    void onCancelClicked();

    void closeEvent(QCloseEvent *event) override;
};

#endif // INPUTDIALOG_H
