#include "../OtoVisionArea.h"

void OtoVisionArea::zoomHorizontally(int delta) {
    // 保存先后的单位长度与鼠标指针坐标
    QPointF absPos = vision->cursorPos();
    QPoint relativePos = scroll->mapFromGlobal(QCursor::pos());

    // 计算变化后widget的目标坐标
    int fromX = relativePos.x();

    if (fromX < 0) {
        fromX = 0;
    } else if (fromX > scroll->width()) {
        fromX = scroll->width();
    }

    int fromW = vision->width();
    int toW = vision->width() + delta;

    int minW = minWidth();
    int maxW = vision->duration() * 2000;

    maxW = (maxW < minW * 4) ? (minW * 4) : maxW;
    toW = (toW < minW) ? minW : toW;
    toW = (toW > maxW) ? maxW : toW;

    if (toW == fromW) {
        return;
    }

    int fromAbs = absPos.x() - (relativePos.x() - fromX);
    int toX = fromX - fromAbs * double(toW) / (fromW);

    if (toX > 0) {
        toX = 0;
    }

    // 编辑区域尺寸调整
    vision->setWidth(toW);

    // 相对坐标调整
    QScrollBar *bar = scroll->horizontalScrollBar();
    bar->setValue(-toX);
}
