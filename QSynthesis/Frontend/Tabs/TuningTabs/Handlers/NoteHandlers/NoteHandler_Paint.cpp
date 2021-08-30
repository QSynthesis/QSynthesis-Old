#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../NoteHandler.h"
#include "Methods.h"

void NoteHandler::drawNote(QPainter *painter) {
    QRectF rect = m_note->rect();

    double padding = 0.25;
    double innerPadding = 2;
    double border = rect.height() / 15;

    border = border > 4 ? 4 : border;

    QColor lineColor = m_note->isRest()
                           ? m_restLineColor
                           : (m_note->isListed() ? m_listedLineColor : m_unlistedLineColor);

    QColor fillColor = m_note->isRest()
                           ? m_restFillColor
                           : (m_note->isListed() ? m_listedFillColor : m_unlistedFillColor);

    QRectF originRect(padding, padding, rect.width() - 2 * padding, rect.height() - 2 * padding);
    QRectF entityRect(originRect);
    QRectF textRect(originRect);
    textRect.setX(entityRect.x() + 5 + m_editor->ptrs()->currentWidth / 128.0);

    painter->setBrush(lineColor);
    painter->setPen(Qt::NoPen);

    entityRect.setTop(entityRect.top() + entityRect.height() * 0.85);
    painter->drawRoundedRect(entityRect, border * 1.5, border * 1.5);

    if (m_note->isSelected()) {
        painter->setBrush(fillColor);
        QRectF innerRect(entityRect.left() + innerPadding, entityRect.top() + innerPadding,
                         entityRect.width() - 2 * innerPadding,
                         entityRect.height() - 2 * innerPadding);

        painter->drawRoundedRect(innerRect, border * 1.5, border * 1.5);

        //        painter->setPen(Qt::NoPen);
        //        painter->setBrush(m_backColor);
        //        painter->drawRoundedRect(originRect, border * 1.5, border * 1.5);
    }

    if (m_editor->curEditNote() != m_note) {
        painter->setPen(m_lyricColor);
        painter->setBrush(Qt::NoBrush);
        painter->setFont(uiFont());

        QString str0 = m_note->Note.lyric;
        painter->drawText(textRect, Qt::AlignVCenter, str0, &entityRect);
    }
}
