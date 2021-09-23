#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>

#include "QUtils.h"

class ImageLabel : public QLabel {
    Q_OBJECT
public:
    ImageLabel(QWidget *parent = nullptr);
    ~ImageLabel();

private:
    void mouseReleaseEvent(QMouseEvent *event) override;

    void handleReplace();

private:
    void init();

signals:
    void reveal();
    void replace(QString path);
    void remove();
};

#endif // IMAGELABEL_H
