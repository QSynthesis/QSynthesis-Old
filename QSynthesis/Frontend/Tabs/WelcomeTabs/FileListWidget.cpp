#include "FileListWidget.h"
#include "Document/SettingIniFile.h"
#include "Templates/TemporaryMenu.h"
#include "mainwindow.h"

FileListWidget::FileListWidget(QWidget *parent) : QListWidget(parent) {
    init();
}

FileListWidget::~FileListWidget() {
}

void FileListWidget::init() {
    m_type = Files;

    delegate = new FileListWidgetItem(this);
    setItemDelegate(delegate);

    setSelectionMode(QAbstractItemView::SingleSelection);

    connect(delegate, &FileListWidgetItem::leftClick, this, &FileListWidget::onLeftClick);
    connect(delegate, &FileListWidgetItem::rightClick, this, &FileListWidget::onRightClick);

    installEventFilter(this);
}

FileListWidget::Type FileListWidget::type() const {
    return m_type;
}

void FileListWidget::setType(const Type &type) {
    m_type = type;
}

int FileListWidget::itemHeight() const {
    return delegate->m_itemHeight;
}

void FileListWidget::setItemHeight(int value) {
    if (value > 1000) {
        return;
    }
    delegate->m_itemHeight = value;
    emit propertyChanged();
}

QColor FileListWidget::selectColor() const {
    return delegate->m_selectColor;
}

void FileListWidget::setSelectColor(const QColor &selectColor) {
    delegate->m_selectColor = selectColor;
    emit propertyChanged();
}

QColor FileListWidget::underlineColor() const {
    return delegate->m_underlineColor;
}

void FileListWidget::setUnderlineColor(const QColor &underlineColor) {
    delegate->m_underlineColor = underlineColor;
    emit propertyChanged();
}

QColor FileListWidget::filenameColor() const {
    return delegate->m_filenameColor;
}

void FileListWidget::setFilenameColor(const QColor &value) {
    delegate->m_filenameColor = value;
    emit propertyChanged();
}

QColor FileListWidget::directoryColor() const {
    return delegate->m_directoryColor;
}

void FileListWidget::setDirectoryColor(const QColor &value) {
    delegate->m_directoryColor = value;
    emit propertyChanged();
}

QColor FileListWidget::dateColor() const {
    return delegate->m_dateColor;
}

void FileListWidget::setDateColor(const QColor &value) {
    delegate->m_dateColor = value;
    emit propertyChanged();
}

void FileListWidget::onLeftClick(QModelIndex index) {
    handleOpen(index.data(Qt::UserRole + 2).toString());
}

void FileListWidget::onRightClick(QModelIndex index) {
    QString filename = index.data(Qt::UserRole + 2).toString();

    QString revealStr;
    if (m_type == Files) {
#if defined(Q_OS_WINDOWS)
        revealStr = tr("Show in Explorer(&S)");
#elif defined(Q_OS_MAC)
        revealStr = tr("Show in Finder(&S)");
#else
        revealStr = tr("Show in File Manager(&S)");
#endif
    } else {
#if defined(Q_OS_WINDOWS)
        revealStr = tr("Open in Explorer(&S)");
#elif defined(Q_OS_MAC)
        revealStr = tr("Open in Finder(&S)");
#else
        revealStr = tr("Open in File Manager(&S)");
#endif
    }

    QStringList list{tr("Open(&O)"), tr("Remove from list(&R)"), revealStr};
    TemporaryMenu *menu = new TemporaryMenu(list, this);
    int action = menu->start();
    menu->deleteLater();

    switch (action) {
    case 0:
        handleOpen(filename);
        break;
    case 1:
        handleRemove(filename);
        break;
    case 2:
        handleReveal(filename);
        break;
    default:
        break;
    }

    itemFromIndex(index)->setSelected(false);
}

bool FileListWidget::eventFilter(QObject *obj, QEvent *event) {
    if (DataManager::keyIsDown(event)) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            QModelIndex index = currentIndex();
            if (index.isValid()) {
                handleOpen(index.data(Qt::UserRole + 2).toString());
            }
        }
    }
    return QListWidget::eventFilter(obj, event);
}

void FileListWidget::handleOpen(const QString &filename) {
    qRoot->addMultipleTabs({filename}, false);
}

void FileListWidget::handleRemove(const QString &filename) {
    removeItemWidget(selectedItems()[0]);
    if (m_type == Files) {
        qSetting->projects.remove(filename);
    } else {
        qSetting->folders.remove(filename);
    }
    qRoot->reloadRecentMenu();
}

void FileListWidget::handleReveal(const QString &filename) {
    RevealFile(filename);
}
