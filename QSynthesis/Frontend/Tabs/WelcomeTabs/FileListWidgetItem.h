#ifndef FILELISTWIDGETITEM_H
#define FILELISTWIDGETITEM_H

#include <QDebug>
#include <QEvent>
#include <QListWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QWidget>

#include "Global/Methods.h"
#include "QUtils.h"

// Recent list items
class FileListWidgetItem : public QStyledItemDelegate {
    Q_OBJECT

public:
    FileListWidgetItem(QObject *pParent);
    ~FileListWidgetItem();

    friend class FileListWidget;

private:
    int m_itemHeight;
    QColor m_selectColor;
    QColor m_underlineColor;

    QColor m_filenameColor;
    QColor m_directoryColor;
    QColor m_dateColor;

    // Determine how to paint
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const override;
    // Determine recommended size
    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override;

    virtual void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                           const QRect &rect) const;

    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model,
                             const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void leftClick(QModelIndex index);
    void rightClick(QModelIndex index);
};

#endif // FILELISTWIDGETITEM_H
