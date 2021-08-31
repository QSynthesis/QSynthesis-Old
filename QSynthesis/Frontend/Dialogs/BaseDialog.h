#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>

class BaseDialog : public QDialog {
    Q_OBJECT
public:
    explicit BaseDialog(QWidget *parent = nullptr);
    virtual ~BaseDialog();
};

#endif // BASEDIALOG_H
