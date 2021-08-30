#ifndef LIFTERSSCROLLAREA_H
#define LIFTERSSCROLLAREA_H

#include "Common/Graphics/GraphicsLinearView.h"

class LiftersScrollArea : public GraphicsLinearView {
public:
    explicit LiftersScrollArea(QWidget *parent = nullptr);
    virtual ~LiftersScrollArea();

    QRectF viewportRect() const;

private:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // LIFTERSSCROLLAREA_H
