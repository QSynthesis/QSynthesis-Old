#include "../OtoTableTab.h"

void OtoTableTab::addRow(const QGenonSettings &genon) {
    insertRow(otoTable->rowCount(), genon);
}

void OtoTableTab::insertRow(int row, const QGenonSettings &genon) {
    QStringList list;
    list.append(PathFindFileName(genon.mFileName));
    list.append(genon.mAlias);
    list.append(QString::number(genon.mOffset));
    list.append(QString::number(genon.mConstant));
    list.append(QString::number(genon.mBlank));
    list.append(QString::number(genon.mPreUtterance));
    list.append(QString::number(genon.mVoiceOverlap));
    list.append(genon.frqExist() ? "TRUE" : "FALSE");
    insertRow(row, list);

    // empty Genon, set line to green
    if (!genon.valid()) {
        turnLineToInvalid(row);
    } else if (genon.isEmpty()) {
        turnLineToEmpty(row);
    }
}

void OtoTableTab::insertRow(int row, const QStringList &list) {
    otoTable->insertRow(row);

    QTableWidgetItem *item = new QTableWidgetItem(list.at(0));
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    otoTable->setItem(row, 0, item);

    otoTable->setItem(row, 1, new QTableWidgetItem(list.at(1)));
    otoTable->setItem(row, 2, new QTableWidgetItem(list.at(2)));
    otoTable->setItem(row, 3, new QTableWidgetItem(list.at(3)));
    otoTable->setItem(row, 4, new QTableWidgetItem(list.at(4)));
    otoTable->setItem(row, 5, new QTableWidgetItem(list.at(5)));
    otoTable->setItem(row, 6, new QTableWidgetItem(list.at(6)));

    QTableWidgetItem *item1 = new QTableWidgetItem(list.at(7));
    item1->setFlags(item->flags() & (~Qt::ItemIsEditable));
    otoTable->setItem(row, 7, item1);
}

void OtoTableTab::removeRow(int row) {
    otoTable->removeRow(row);
}

void OtoTableTab::selectNone() {
    QTableWidgetSelectionRange all(0, 0, otoTable->rowCount() - 1, otoTable->columnCount() - 1);
    otoTable->setRangeSelected(all, false);
}

void OtoTableTab::selectRow(int row) {
    QTableWidgetItem *item = otoTable->item(row, 0);
    otoTable->scrollToItem(item);

    selectNone();
    QTableWidgetSelectionRange range(row, 0, row, otoTable->columnCount() - 1);
    otoTable->setCurrentItem(item);
    otoTable->setRangeSelected(range, true);
}

void OtoTableTab::swapRow(int row1, int row2) {
    QString temp;
    for (int i = 0; i < otoTable->columnCount(); ++i) {
        temp = otoTable->item(row1, i)->text();
        otoTable->item(row1, i)->setText(otoTable->item(row2, i)->text());
        otoTable->item(row2, i)->setText(temp);
    }
}

void OtoTableTab::moveRow(int from, int to) {
    QGenonSettings genon = getGenonSettings(from);
    removeRow(from);
    insertRow(to, genon);
}
