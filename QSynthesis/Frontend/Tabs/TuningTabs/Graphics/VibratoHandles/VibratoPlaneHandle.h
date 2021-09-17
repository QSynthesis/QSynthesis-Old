#ifndef VIBRATOPLANEHANDLE_H
#define VIBRATOPLANEHANDLE_H

#include "Graphics/GraphicsPlaneHandle.h"
#include "QUtils.h"
#include "VibratoBaseHandle.h"

class VibratoPlaneHandle : public VibratoObject, public GraphicsPlaneHandle {
    Q_OBJECT
public:
    explicit VibratoPlaneHandle(NotesArea *editor, Mode2Handler *scope,
                                QGraphicsItem *parent = nullptr);
    ~VibratoPlaneHandle();

    void updateColorTheme();

private:
    void init();

public:
    QString text() const;
    void setText(const QString &text);

    QColor borderColor() const;
    void setBorderColor(const QColor &borderColor);

    QColor textColor() const;
    void setTextColor(const QColor &textColor);

    QColor fillColor() const;
    void setFillColor(const QColor &fillColor);

    double ringWidth() const;
    void setRingWidth(double ringWidth);

    double padding() const;
    void setPadding(double padding);

protected:
    MorePoint limitArea(MorePoint origin) override;

private:
    QString m_text;

    QColor m_borderColor, m_textColor, m_fillColor;
    double m_ringWidth;
    double m_padding;

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

#endif // VIBRATOPLANEHANDLE_H
