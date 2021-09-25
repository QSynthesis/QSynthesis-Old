#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include "Controls/SlideControl.h"

class FindReplaceDialog : public QWidget {
    Q_OBJECT
public:
    explicit FindReplaceDialog(QWidget *parent = nullptr);
    ~FindReplaceDialog();

signals:
};

#endif // FINDREPLACEDIALOG_H
