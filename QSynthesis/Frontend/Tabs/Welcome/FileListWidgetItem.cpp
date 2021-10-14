#include "FileListWidgetItem.h"

FileListWidgetItem::FileListWidgetItem(QObject *pParent) : QStyledItemDelegate(pParent) {
    m_itemHeight = 72;
    m_selectColor = Qt::lightGray;
    m_underlineColor = Qt::lightGray;

    m_filenameColor = Qt::black;
    m_directoryColor = Qt::darkGray;
    m_dateColor = QColor(0x666666);
}

FileListWidgetItem::~FileListWidgetItem() {
}

void FileListWidgetItem::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
    QFont bigFont = mainFont(17);
    QFont smallFont = mainFont();

    QRect fullRect = option.rect; // 目标矩形
    QRect rect = fullRect;        // 目标矩形

    int paddingW = 25;
    int paddingH = 8;
    int spacing = 80;

    int fileNameWidth;
    int filePathWidth;
    int dateWidth;
    int maxLeftWidth;

    rect.adjust(paddingW, paddingH, -paddingW, -paddingH); // 缩小一圈，留出空白间隔

    // 取得该项对应的数据
    QString fileName = index.data(Qt::DisplayRole).toString();
    QString lastOpenTime = index.data(Qt::UserRole + 1).toString();
    QString fileLocation = QDir::toNativeSeparators(index.data(Qt::UserRole + 2).toString());

    painter->setRenderHint(QPainter::Antialiasing);

    // 状态显示: 若该项被选中
    if (option.state & QStyle::State_Selected) {
        painter->setBrush(m_selectColor);
        painter->setPen(Qt::NoPen);
        painter->drawRect(fullRect);
        painter->setBrush(Qt::NoBrush);
    } else if (option.state & QStyle::State_MouseOver) {
        painter->setBrush(m_selectColor);
        painter->setPen(Qt::NoPen);
        painter->drawRect(fullRect);
        painter->setBrush(Qt::NoBrush);
    }

    painter->setPen(Qt::black);

    // 图片显示 如果有区分的图标的话可以保留
    //    {
    //        QRect dst = rect;
    //        dst.setRight(rect.left() + 40);
    //        QRect area(0,0,24,24);
    //        area.moveCenter(dst.center());

    //        QPixmap pixmapPic(qstrRecordPic);
    //        painter->drawPixmap(area, pixmapPic);

    //    }

    painter->setFont(smallFont);
    painter->setPen(m_dateColor);

    // 文件最后打开时间
    {
        QRect dst = rect;
        QString str = lastOpenTime;

        dateWidth = QFontMetrics(painter->font()).horizontalAdvance(str);
        painter->drawText(dst, Qt::AlignRight | Qt::AlignVCenter, str);
    }

    maxLeftWidth = (rect.width() - dateWidth) - spacing;

    painter->setFont(bigFont);
    painter->setPen(m_filenameColor);

    // 文件名显示
    {
        QRect dst = rect;
        QString str = fileName;
        dst.setBottom(rect.top() + rect.height() / 2);

        fileNameWidth = QFontMetrics(painter->font()).horizontalAdvance(str);
        if (fileNameWidth > maxLeftWidth) {
            str = QFontMetrics(painter->font()).elidedText(str, Qt::ElideRight, maxLeftWidth);
        }
        painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, str);
    }

    painter->setFont(smallFont);
    painter->setPen(m_directoryColor);
    // 文件地址
    {
        QRect dst = rect;
        QString str = fileLocation;
        dst.setTop(rect.top() + rect.height() / 2);

        filePathWidth = QFontMetrics(painter->font()).horizontalAdvance(str);
        if (filePathWidth > maxLeftWidth) {
            str = QFontMetrics(painter->font()).elidedText(str, Qt::ElideRight, maxLeftWidth);
        }
        painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, str);
    }

    painter->setPen(QPen(m_underlineColor, 1));
    painter->drawLine(fullRect.bottomLeft(), fullRect.bottomRight());
}

QSize FileListWidgetItem::sizeHint(const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(m_itemHeight);
    return size;
}

void FileListWidgetItem::drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                                   const QRect &rect) const {
    // qDebug() << "focus";
}

bool FileListWidgetItem::editorEvent(QEvent *event, QAbstractItemModel *model,
                                     const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        if (mouseEvent->button() == Qt::RightButton) {
            emit rightClick(index);
        } else if (mouseEvent->button() == Qt::LeftButton) {
            emit leftClick(index);
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
