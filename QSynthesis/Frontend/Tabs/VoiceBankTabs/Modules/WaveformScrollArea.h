#ifndef WAVEFORMSCROLLAREA_H
#define WAVEFORMSCROLLAREA_H

#include "Common/Graphics/GraphicsLinearView.h"

class WaveformScrollArea : public GraphicsLinearView {
    Q_OBJECT
public:
    explicit WaveformScrollArea(QWidget *parent = nullptr);
    ~WaveformScrollArea();

    QRectF viewportRect() const;

private:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // WAVEFORMSCROLLAREA_H
