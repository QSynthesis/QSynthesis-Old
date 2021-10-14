#include "../../Editor/Areas/NotesArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsNote.h"

void GraphicsNote::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
    drawNote(painter);
}

void GraphicsNote::drawNote(QPainter *painter) {
    QRectF rect = this->rect();
    bool selected = isSelected();

    double padding = 0.5;
    double innerPadding = 2;
    double border = rect.height() / 15;

    border = border > 4 ? 4 : border;

    QColor lineColor =
        isRest() ? m_restLineColor : (isListed() ? m_listedLineColor : m_unlistedLineColor);

    QColor fillColor =
        isRest() ? m_restFillColor : (isListed() ? m_listedFillColor : m_unlistedFillColor);

    QRectF originRect(padding, padding, rect.width() - 2 * padding, rect.height() - 2 * padding);
    QRectF entityRect(originRect);
    QRectF textRect(originRect);
    textRect.setX(entityRect.x() + 5 + m_editor->ptrs()->currentWidth / 128.0);

    if (!m_block) {
        // Draw Back
        if (selected) {
            painter->setPen(Qt::NoPen);
            painter->setBrush(m_selectColor);
            painter->drawRoundedRect(rect, 3, 3);
        }
        entityRect.setTop(entityRect.top() + entityRect.height() * 0.85);
    }

    // Draw Entity
    painter->setBrush(lineColor);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(entityRect, border * 1.5, border * 1.5);

    // Draw Line
    if (selected) {
        painter->setBrush(fillColor);
        QRectF innerRect(entityRect.left() + innerPadding, entityRect.top() + innerPadding,
                         entityRect.width() - 2 * innerPadding,
                         entityRect.height() - 2 * innerPadding);

        painter->drawRoundedRect(innerRect, border * 1.5, border * 1.5);
    }

    if (m_editor->curEditNote() != this) {
        painter->setPen(m_block ? m_lyricBlockColor : m_lyricColor);
        painter->setBrush(Qt::NoBrush);
        painter->setFont(uiFont());

        QString str0 = Note.lyric;
        painter->drawText(textRect, Qt::AlignVCenter, str0, &entityRect);
    }
}

void GraphicsNote::drawParams(QPainter *painter) {
    double mod = modulation();

    QString strMod = (mod == 0) ? "" : ("Mod " + QString::number(mod));
    QString strFlags = Note.flags;

    QString strPara =
        strMod.isEmpty() ? strFlags : (strMod + (strFlags.isEmpty() ? "" : " / ") + strFlags);

    int f = (y() + height() * 1.5 >= m_screen->boundingRect().height()) ? -1 : 1;

    QRectF entityRect(0, y() + f * height(), width(), height());
    QRectF textRect(entityRect);
    textRect.setX(entityRect.x() + 5 + m_editor->ptrs()->currentWidth / 128.0);

    painter->setPen(m_paramsColor);
    painter->setBrush(Qt::transparent);
    painter->setFont(uiFont());
    painter->drawText(textRect, Qt::AlignVCenter, strPara, &entityRect);
}

void GraphicsNote::drawHighlight(QPainter *painter) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(m_highlightColor));

    QRectF rect = m_screen->boundingRect();
    rect.setLeft(x() - m_screen->x());
    rect.setWidth(width());
    painter->drawRect(rect);
}
