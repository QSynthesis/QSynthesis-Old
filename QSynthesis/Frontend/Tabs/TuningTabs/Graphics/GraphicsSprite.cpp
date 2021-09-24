#include "GraphicsSprite.h"

GraphicsSprite::GraphicsSprite(NotesArea *editor, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), m_editor(editor) {
    setTransformationMode(Qt::SmoothTransformation);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

GraphicsSprite::~GraphicsSprite() {
}

QPainterPath GraphicsSprite::shape() const {
    return QPainterPath();
}

QVariant GraphicsSprite::itemChange(QGraphicsItem::GraphicsItemChange change,
                                    const QVariant &value) {
    return QGraphicsPixmapItem::itemChange(change, value);
}
