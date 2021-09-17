#ifndef GRAPHICSRUBBER_H
#define GRAPHICSRUBBER_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QTimer>

class NotesArea;

class GraphicsRubber : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    explicit GraphicsRubber(NotesArea *editor, QGraphicsItem *parent = nullptr);
    ~GraphicsRubber();

    void updateColorTheme();

    void setStartPoint(QPointF Fpos);
    void setEndPoint(QPointF pos);

    bool active() const;
    void setActive(bool active);

    QColor frameColor() const;
    void setFrameColor(const QColor &frameColor);

    QColor fillColor() const;
    void setFillColor(const QColor &fillColor);

    bool vertical() const;
    void setVertical(bool vertical);

private:
    NotesArea *m_editor;

    QPointF m_start, m_end;
    QTimer *m_timer;

    QColor m_frameColor;
    QColor m_fillColor;

    bool m_active;

    bool m_vertical;

    void init();
    void onTimer();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void selecting();
    void selectOver();
};

#endif // GRAPHICSRUBBER_H
