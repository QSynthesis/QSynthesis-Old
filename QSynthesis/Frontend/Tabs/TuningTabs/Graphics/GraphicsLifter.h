#ifndef GRAPHICSLIFTER_H
#define GRAPHICSLIFTER_H

#include "Graphics/GraphicsLineHandle.h"
#include "QUtils.h"

class GraphicsNote;
class LiftersArea;

class GraphicsLifter : public GraphicsLineHandle {
public:
    explicit GraphicsLifter(GraphicsNote *note, LiftersArea *editor,
                            QGraphicsItem *parent = nullptr);
    virtual ~GraphicsLifter();

    static int Radius;

    enum Props { Intensity, Modulation, Velocity, Undefined };

    friend class DraggerHandler;

public:
    QColor activeColor() const;
    void setActiveColor(const QColor &activeColor);

    QColor inactiveColor() const;
    void setInactiveColor(const QColor &inactiveColor);

    QColor activeHColor() const;
    void setActiveHColor(const QColor &activeHColor);

    QColor inactiveHColor() const;
    void setInactiveHColor(const QColor &inactiveHColor);

    GraphicsNote *note() const;
    LiftersArea *editor() const;

    Props prop() const;
    void setProp(const Props &prop);

    bool active() const;
    void setActive(bool active);

    bool highlighted() const;
    void setHighlighted(bool highlighted);

private:
    QColor m_activeColor;
    QColor m_inactiveColor;

    QColor m_activeHColor;
    QColor m_inactiveHColor;

    // Variate
public:
    void fromNoteProps(Props prop = Undefined);
    void toNoteProps(Props prop = Undefined);

    void setValue(double value) override;

    // States
public:
    void adjustSize();
    void adjustHandle();

    void fromHandle();

    // Assist
public:
    static double convertRatioToProp(Props prop, double ratio);
    static double convertPropToRatio(Props prop, double props);

private:
    GraphicsNote *m_note;
    LiftersArea *m_editor;

    Props m_prop;

    bool m_active;
    bool m_highlighted;

    QRectF m_geometry;

    QMap<Props, double> m_values;

    // Link
private:
    MorePoint limitArea(MorePoint origin) override;
    MorePoint limitAreaT(MorePoint origin) override;

    void linkMove(QPointF pos) override;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    QRectF boundingRect() const override;

public:
    void afterPress();
    void afterMove(QPointF pos);
    void afterRelease();
};

#endif // GRAPHICSLIFTER_H
