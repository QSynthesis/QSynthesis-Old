#ifndef GRAPHICSLINES_H
#define GRAPHICSLINES_H

#include <QGraphicsRectItem>

class GraphicsNote;
class NotesArea;

class GraphicsLines : public QGraphicsItem {
public:
    explicit GraphicsLines(GraphicsNote *note, NotesArea *editor, QGraphicsItem *parent = nullptr);
    ~GraphicsLines();

    GraphicsNote *note() const;
    NotesArea *editor() const;

public:
    void updateLocation();
    void updateSize();

private:
    GraphicsNote *m_note;
    NotesArea *m_editor;

    QRectF m_rect;

    int type() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

public:
    QRectF boundingRect() const override;
};

#endif // GRAPHICSLINES_H
