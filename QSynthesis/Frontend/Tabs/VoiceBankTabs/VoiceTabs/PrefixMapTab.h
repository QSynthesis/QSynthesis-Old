#ifndef PREFIXMAPTAB_H
#define PREFIXMAPTAB_H

#include <QHeaderView>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "../../BaseTab.h"

class PrefixMapTab : public BaseTab {
    Q_OBJECT
public:
    explicit PrefixMapTab(TabWidget *parent = nullptr);

    void setPrefix(int noteNum, QString value);
    void setSuffix(int noteNum, QString value);

    QString prefix(int noteNum) const;
    QString suffix(int noteNum) const;

public:
    void selectTone(int noteNum);

private:
    QTableWidget *mapTable;
    QVBoxLayout *mainLayout;

    void init();
    void initTable();

    QTableWidgetItem *fetchItemCore(int noteNum, int columnIndex) const;
    void handleCellChanged(int row, int column);

private:
    int convertToneToRow(int noteNum) const;
    int convertRowToTone(int row) const;

signals:
    void prefixChanged(int noteNum, QString value);
    void suffixChanged(int noteNum, QString value);
};

#endif // PREFIXMAPTAB_H
