#include "../../../../TuningTab.h"
#include "../../../Scrolls/NotesScrollArea.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::initSpriteModules() {
    sprite = new GraphicsSprite(this);
    addItem(sprite);
    sprite->setZValue(spriteZIndex);
    sprite->setVisible(false);
}

void NotesArea::updateSprite() {
    if (sprite->pixmap().isNull()) {
        return;
    }
    if (!m_spriteVisible) {
        if (sprite->isVisible()) {
            sprite->hide();
        }
        return;
    } else {
        sprite->show();
    }

    QSize size = sprite->pixmap().size();
    QRectF rect = m_view->viewportRect();

    double scale = rect.height() / size.height();
    if (scale * size.width() > rect.width()) {
        scale = rect.width() / size.width();
    }
    sprite->setScale(scale);

    QSizeF realSize = size * scale;
    sprite->setPos(rect.x() + rect.width() - realSize.width(),
                   rect.y() + rect.height() - realSize.height());
    sprite->setOpacity(0.3);
}

void NotesArea::reloadSprite() {
    QPixmap bmp;
    if (m_ptrs->tab->oto && bmp.load(m_ptrs->tab->oto->spritePath())) {
        sprite->setPixmap(bmp);
    } else {
        sprite->setPixmap(QPixmap());
    }
    updateSprite();
}
