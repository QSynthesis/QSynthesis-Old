#ifndef VIBRATOLINEHANDLE_H
#define VIBRATOLINEHANDLE_H

#include "Graphics/GraphicsLineHandle.h"
#include "QUtils.h"
#include "VibratoBaseHandle.h"

class VibratoLineHandle : public VibratoObject, public GraphicsLineHandle {
    Q_OBJECT
public:
    explicit VibratoLineHandle(Qt::Orientation orient, NotesArea *editor, Mode2Handler *scope,
                               QGraphicsItem *parent = nullptr);
    ~VibratoLineHandle();

private:
    void init();

protected:
    void updateRect();
    QPointF limitArea(QPointF origin) override;

public:
    void setRegion(const QRectF &region = NO_RECTF) override;

    double lineWidth() const;
    void setLineWidth(double lineWidth);

    QColor lineColor() const;
    void setLineColor(const QColor &lineColor);

    bool showLine() const;
    void setShowLine(bool show);

private:
    bool m_show;

    double m_lineWidth;
    QColor m_lineColor;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

public:
    void afterPress();
    void afterMove(QPointF pos);
    void afterRelease();
};

#endif // VIBRATOLINEHANDLE_H
