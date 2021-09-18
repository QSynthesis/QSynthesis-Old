#ifndef KEYLINEEDIT_H
#define KEYLINEEDIT_H

#include <QKeyEvent>

#include "Controls/FixedLineEdit.h"

class KeyLineEdit : public FixedLineEdit {
    Q_OBJECT
public:
    explicit KeyLineEdit(QWidget *parent = nullptr);

public:
    void setKey(int key);
    int key() const;

    void setText(QString qsText);

signals:
    void keyChange(int key);
    void enterModify();
    void abandon();

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    int m_key;
};

#endif // KEYLINEEDIT_H
