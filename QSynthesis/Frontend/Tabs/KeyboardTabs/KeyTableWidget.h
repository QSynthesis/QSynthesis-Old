#ifndef KEYTABLEWIDGET_H
#define KEYTABLEWIDGET_H

#include <QHeaderView>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPainter>
#include <QPushButton>
#include <QSvgRenderer>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "KeyLabelContent.h"
#include "KeyModifyWidget.h"

#include "Methods.h"
#include "QUtils.h"

#include "Data/ShortcutsData.h"

// A modified table widget.
class KeyTableWidget : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout *mainLayout;
    QTableWidget *myTable;

    int preRow;
    QColor preColor;

    QVector<QStringList> dataList;
    QPixmap editIcon;

public:
    explicit KeyTableWidget(QWidget *parent = nullptr);
    bool load(const ShortcutsData &keys);
    void setRowColor(int row, QColor color, bool in = true);

    QTableWidget *table();
    QVector<QStringList> &data();

protected:
    void leaveEvent(QEvent *e) override;

private:
    void onCellEntered(int row, int column);
    void onDoubleClicked(int row);

public:
    void setKey(int id, QString key);

signals:
    void keyModified(int row, QString keyBind);
};

#endif // KEYTABLEWIDGET_H
