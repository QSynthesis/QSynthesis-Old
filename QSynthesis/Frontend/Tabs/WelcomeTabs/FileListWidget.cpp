#include "FileListWidget.h"
#include "mainwindow.h"

FileListWidget::FileListWidget(QWidget *parent) : QListWidget(parent) {
    init();
}

FileListWidget::~FileListWidget() {
}

void FileListWidget::init() {
    m_type = Files;
    currentFileName = "";
    m_menu = new QMenu(this);

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
    currentFileName = index.data(Qt::UserRole + 2).toString();
    handleOpen();
}

void FileListWidget::onRightClick(QModelIndex index) {
    currentFileName = index.data(Qt::UserRole + 2).toString();

    QAction *openAction = new QAction(m_menu);
    QAction *deleteAction = new QAction(m_menu);
    QAction *revealAction = new QAction(m_menu);

    openAction->setText(tr("Open(&O)"));
    deleteAction->setText(tr("Remove from list(&R)"));

    if (m_type == Files) {
#if defined(Q_OS_WINDOWS)
        revealAction->setText(tr("Show in Explorer(&S)"));
#elif defined(Q_OS_MAC)
        revealAction->setText(tr("Show in Finder(&S)"));
#else
        revealAction->setText(tr("Show in File Manager(&S)"));
#endif
    } else {
#if defined(Q_OS_WINDOWS)
        revealAction->setText(tr("Open in Explorer(&S)"));
#elif defined(Q_OS_MAC)
        revealAction->setText(tr("Open in Finder(&S)"));
#else
        revealAction->setText(tr("Open in File Manager(&S)"));
#endif
    }

    connect(openAction, &QAction::triggered, this, &FileListWidget::handleOpen);
    connect(deleteAction, &QAction::triggered, this, &FileListWidget::handleDelete);
    connect(revealAction, &QAction::triggered, this, &FileListWidget::handleReveal);

    m_menu->addAction(openAction);
    m_menu->addAction(deleteAction);
    m_menu->addAction(revealAction);

    m_menu->exec(QCursor::pos());
    m_menu->clear();

    itemFromIndex(index)->setSelected(false);
}

bool FileListWidget::eventFilter(QObject *obj, QEvent *event) {
    if (AppAssistant::keyIsDown(event)) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            QModelIndex index = currentIndex();
            if (index.isValid()) {
                currentFileName = index.data(Qt::UserRole + 2).toString();
                handleOpen();
            }
        }
    }
    return QListWidget::eventFilter(obj, event);
}

void FileListWidget::handleOpen() {
    if (m_type == Files) {
        qRoot->addTuningTab(currentFileName, false);
    } else {
        qRoot->addVoiceBankTab(currentFileName);
    }
}

void FileListWidget::handleDelete() {
    removeItemWidget(selectedItems()[0]);
    if (m_type == Files) {
        qSetting->projects.remove(currentFileName);
    } else {
        qSetting->folders.remove(currentFileName);
    }
    qRoot->reloadRecentMenu();
}

void FileListWidget::handleReveal() {
    RevealFile(currentFileName);
}
