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
    openTriggered();
}

void FileListWidget::onRightClick(QModelIndex index) {
    currentFileName = index.data(Qt::UserRole + 2).toString();

    QAction *openAction = new QAction(m_menu);
    QAction *deleteAction = new QAction(m_menu);
    QAction *revealAction = new QAction(m_menu);

    openAction->setText(tr("Open(&O)"));
    deleteAction->setText(tr("Remove from list(&R)"));

    if (m_type == Files) {
#if defined(_WIN32)
        revealAction->setText(tr("Show in Explorer(&S)"));
#elif defined(__APPLE__)
        revealAction->setText(tr("Show in Finder(&S)"));
#else
        revealAction->setText(tr("Show in File Manager(&S)"));
#endif
    } else {
#if defined(_WIN32)
        revealAction->setText(tr("Open in Explorer(&S)"));
#elif defined(__APPLE__)
        revealAction->setText(tr("Open in Finder(&S)"));
#else
        revealAction->setText(tr("Open in File Manager(&S)"));
#endif
    }

    connect(openAction, &QAction::triggered, this, &FileListWidget::openTriggered);
    connect(deleteAction, &QAction::triggered, this, &FileListWidget::deleteTriggered);
    connect(revealAction, &QAction::triggered, this, &FileListWidget::revealTriggered);

    m_menu->addAction(openAction);
    m_menu->addAction(deleteAction);
    m_menu->addAction(revealAction);

    m_menu->exec(QCursor::pos());
    m_menu->clear();

    setItemSelected(itemFromIndex(index), false);
}

void FileListWidget::openTriggered() {
    if (m_type == Files) {
        Root(this)->addTuningTab(currentFileName, false);
    } else {
        Root(this)->addVoiceBankTab(currentFileName);
    }
}

void FileListWidget::deleteTriggered() {
    removeItemWidget(selectedItems()[0]);
    if (m_type == Files) {
        MainWindow::settingIni.projects.remove(currentFileName);
    } else {
        MainWindow::settingIni.folders.remove(currentFileName);
    }
    Root(this)->reloadRecentMenu();
}

void FileListWidget::revealTriggered() {
    RevealFile(currentFileName);
}
