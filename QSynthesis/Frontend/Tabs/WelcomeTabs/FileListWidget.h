#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QAction>
#include <QContextMenuEvent>
#include <QDebug>
#include <QListWidget>
#include <QMenu>

#include "FileListWidgetItem.h"
#include "QUtils.h"

class FileListWidget : public QListWidget {
    Q_OBJECT
    Q_PROPERTY(int itemHeight READ itemHeight WRITE setItemHeight NOTIFY propertyChanged)
    Q_PROPERTY(QColor selectColor READ selectColor WRITE setSelectColor NOTIFY propertyChanged)
    Q_PROPERTY(
        QColor underlineColor READ underlineColor WRITE setUnderlineColor NOTIFY propertyChanged)
    Q_PROPERTY(
        QColor filenameColor READ filenameColor WRITE setFilenameColor NOTIFY propertyChanged)
    Q_PROPERTY(
        QColor directoryColor READ directoryColor WRITE setDirectoryColor NOTIFY propertyChanged)
    Q_PROPERTY(QColor dateColor READ dateColor WRITE setDateColor NOTIFY propertyChanged)

public:
    enum Type { Files, Folders };
    explicit FileListWidget(QWidget *parent = nullptr);
    ~FileListWidget();

    Type type() const;
    void setType(const Type &type);

    int itemHeight() const;
    void setItemHeight(int value);

    QColor selectColor() const;
    void setSelectColor(const QColor &selectColor);

    QColor underlineColor() const;
    void setUnderlineColor(const QColor &underlineColor);

    QColor filenameColor() const;
    void setFilenameColor(const QColor &value);

    QColor directoryColor() const;
    void setDirectoryColor(const QColor &value);

    QColor dateColor() const;
    void setDateColor(const QColor &value);

signals:
    void propertyChanged();

private:
    QMenu *m_menu;
    Type m_type;

    FileListWidgetItem *delegate;

    QString currentFileName;

    void init();

    void onLeftClick(QModelIndex index);
    void onRightClick(QModelIndex index);

    void openTriggered();
    void deleteTriggered();
    void revealTriggered();
};

#endif // FILELISTWIDGET_H
