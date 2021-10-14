#ifndef IMAGESCROLLAREA_H
#define IMAGESCROLLAREA_H

#include <QScrollArea>

class ImageScrollArea : public QScrollArea {
    Q_OBJECT
public:
    explicit ImageScrollArea(QWidget *parent = nullptr);
    ~ImageScrollArea();

private:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
};

#endif // IMAGESCROLLAREA_H
