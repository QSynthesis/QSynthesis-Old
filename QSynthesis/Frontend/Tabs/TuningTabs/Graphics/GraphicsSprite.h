#ifndef GRAPHICSSPRITE_H
#define GRAPHICSSPRITE_H

#include <QDebug>
#include <QGraphicsPixmapItem>

class NotesArea;

class GraphicsSprite : public QGraphicsPixmapItem {
public:
    explicit GraphicsSprite(NotesArea *editor, QGraphicsItem *parent = nullptr);
    ~GraphicsSprite();

private:
    NotesArea *m_editor;

    QPainterPath shape() const override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // GRAPHICSSPRITE_H
