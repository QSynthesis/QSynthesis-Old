#ifndef GRAPHICSOTOHANDLE_H
#define GRAPHICSOTOHANDLE_H

#include <QObject>
#include <QPropertyAnimation>

#include "Base/Graphics/GraphicsLineHandle.h"
#include "QUtils.h"

class WaveformArea;

class GraphicsOtoHandle : public QObject, public GraphicsLineHandle {
    Q_OBJECT

    Q_PROPERTY(double dynamicLineWidth READ dynamicLineWidth WRITE setDynamicLineWidth NOTIFY
                   dynamicLineWidthChanged)
public:
    explicit GraphicsOtoHandle(WaveformArea *editor, QGraphicsItem *parent = nullptr);
    ~GraphicsOtoHandle();

public:
    double lineWidth() const;
    void setLineWidth(double lineWidth);

    double rectWidth() const;
    void setRectWidth(double rectWidth);

    QColor lineColor() const;
    void setLineColor(const QColor &lineColor);

    double dynamicLineWidth() const;
    void setDynamicLineWidth(double dynamicLineWidth);

protected:
    void updateRect();
    MorePoint limitArea(MorePoint origin) override;

public:
    void setRegion(const QRectF &region = NO_RECTF) override;
    void setPosition(double position) override;

private:
    WaveformArea *m_editor;

    double m_lineWidth;
    double m_rectWidth;

    double m_dynamicLineWidth;
    QPropertyAnimation *m_hoverAnimation;

    QColor m_lineColor;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
              QWidget *widget = nullptr) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
    void afterPress();
    void afterMove(QPointF pos);
    void afterRelease();

signals:
    void pressed();
    void moved(QPointF newPos, QPointF orgPos);
    void clicked();

    void positionChanged();
    void dynamicLineWidthChanged(double value);
};

#endif // GRAPHICSOTOHANDLE_H
