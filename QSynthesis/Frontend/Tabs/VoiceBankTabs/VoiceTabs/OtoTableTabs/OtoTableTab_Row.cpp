#include "../OtoTableTab.h"

void OtoTableTab::addRow(const QGenonSettings &genon) {
    insertRow(table->rowCount(), genon);
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
    table->insertRow(row);

    QTableWidgetItem *item = new QTableWidgetItem(list.at(0));
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    table->setItem(row, 0, item);

    table->setItem(row, 1, new QTableWidgetItem(list.at(1)));
    table->setItem(row, 2, new QTableWidgetItem(list.at(2)));
    table->setItem(row, 3, new QTableWidgetItem(list.at(3)));
    table->setItem(row, 4, new QTableWidgetItem(list.at(4)));
    table->setItem(row, 5, new QTableWidgetItem(list.at(5)));
    table->setItem(row, 6, new QTableWidgetItem(list.at(6)));

    QTableWidgetItem *item1 = new QTableWidgetItem(list.at(7));
    item1->setFlags(item->flags() & (~Qt::ItemIsEditable));
    table->setItem(row, 7, item1);
}

void OtoTableTab::removeRow(int row) {
    table->removeRow(row);
}

void OtoTableTab::swapRow(int row1, int row2) {
    QString temp;
    for (int i = 0; i < table->columnCount(); ++i) {
        temp = table->item(row1, i)->text();
        table->item(row1, i)->setText(table->item(row2, i)->text());
        table->item(row2, i)->setText(temp);
    }
}

void OtoTableTab::moveRow(int from, int to) {
    QGenonSettings genon = getGenonSettings(from);
    removeRow(from);
    insertRow(to, genon);
}

void OtoTableTab::selectAll() {
    table->selectAll();
}

void OtoTableTab::selectNone() {
    const QList<QTableWidgetSelectionRange> &ranges = table->selectedRanges();
    for (int i = 0; i < ranges.size(); ++i) {
        table->setRangeSelected(ranges.at(i), false);
    }
}

void OtoTableTab::selectRow(int row) {
    QTableWidgetItem *item = table->item(row, 0);
    table->scrollToItem(item);

    QTableWidgetSelectionRange range(row, 0, row, table->columnCount() - 1);
    table->setCurrentItem(item);
    table->setRangeSelected(range, true);
}

QList<QTableWidgetSelectionRange> OtoTableTab::selectedRanges() const {
    return table->selectedRanges();
}
