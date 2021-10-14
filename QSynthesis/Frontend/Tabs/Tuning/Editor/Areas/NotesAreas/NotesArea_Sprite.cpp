#include "../../../Scrolls/NotesScrollArea.h"
#include "../../../TuningGroup.h"
#include "../../../TuningTab.h"
#include "../NotesArea.h"

void NotesArea::initSpriteModules() {
    sprite = new GraphicsSprite(this);
    addItem(sprite);
    sprite->setZValue(spriteZIndex);
    sprite->setVisible(false);
}

void NotesArea::updateSprite() {
    if (!m_spriteVisible || sprite->pixmap().isNull()) {
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

    switch (m_spritePosition) {
    case Qt::TopLeftCorner:
        sprite->setPos(rect.x(), rect.y());
        break;
    case Qt::TopRightCorner:
        sprite->setPos(rect.x() + rect.width() - realSize.width(), rect.y());
        break;
    case Qt::BottomLeftCorner:
        sprite->setPos(rect.x(), rect.y() + rect.height() - realSize.height());
        break;
    default:
        sprite->setPos(rect.x() + rect.width() - realSize.width(),
                       rect.y() + rect.height() - realSize.height());
        break;
    }
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
