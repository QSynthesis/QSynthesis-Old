#include "PrefixMapTab.h"
#include "QUtauConstants.h"
#include "QUtauUtils.h"

PrefixMapTab::PrefixMapTab(TabWidget *parent) : BaseTab(parent) {
    init();
}

void PrefixMapTab::setPrefix(int noteNum, QString value) {
    mapTable->blockSignals(true);

    QTableWidgetItem *item = fetchItemCore(noteNum, 1);
    item->setText(value);

    mapTable->blockSignals(false);
}

void PrefixMapTab::setSuffix(int noteNum, QString value) {
    mapTable->blockSignals(true);

    QTableWidgetItem *item = fetchItemCore(noteNum, 2);
    item->setText(value);

    mapTable->blockSignals(false);
}

QString PrefixMapTab::prefix(int noteNum) const {
    QTableWidgetItem *item = fetchItemCore(noteNum, 1);
    return item->text();
}

QString PrefixMapTab::suffix(int noteNum) const {
    QTableWidgetItem *item = fetchItemCore(noteNum, 2);
    return item->text();
}

void PrefixMapTab::selectTone(int noteNum) {
    int row = convertToneToRow(noteNum);
    if (row < 0 || row >= mapTable->rowCount()) {
        return;
    }
    mapTable->selectRow(row);
    mapTable->setFocus();
}

void PrefixMapTab::init() {
    mapTable = new QTableWidget(this);
    mapTable->setProperty("type", "voice");
    mapTable->setColumnCount(3);

    QStringList headerList{tr("Pitch"), tr("Prefix"), tr("Suffix")};
    mapTable->setHorizontalHeaderLabels(headerList);
    // mapTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    mapTable->horizontalHeader()->setDisabled(false);
    // mapTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mapTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    mapTable->setAlternatingRowColors(true);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->addWidget(mapTable);
    setLayout(mainLayout);

    initTable();
}

void PrefixMapTab::initTable() {
    int bottom = TONE_NUMBER_BASE;
    int top = bottom + (TONE_OCTAVE_MAX - TONE_OCTAVE_MIN + 1) * TONE_OCTAVE_STEPS - 1;

    for (int i = top; i >= bottom; --i) {
        int countRow = mapTable->rowCount();
        mapTable->insertRow(countRow);

        QTableWidgetItem *toneItem = new QTableWidgetItem(tone_number_to_tone_name(i));
        toneItem->setFlags(toneItem->flags() & ~Qt::ItemIsEditable);

        mapTable->setItem(countRow, 0, toneItem);
        mapTable->setItem(countRow, 1, new QTableWidgetItem());
        mapTable->setItem(countRow, 2, new QTableWidgetItem());
    }

    connect(mapTable, &QTableWidget::cellChanged, this, &PrefixMapTab::handleCellChanged);
}

QTableWidgetItem *PrefixMapTab::fetchItemCore(int noteNum, int columnIndex) const {
    int rowIndex = convertToneToRow(noteNum);
    QTableWidgetItem *item = mapTable->item(rowIndex, columnIndex);
    return item;
}

void PrefixMapTab::handleCellChanged(int row, int column) {
    int noteNum = convertRowToTone(row);
    QString value = mapTable->item(row, column)->text();

    if (column == 1) {
        emit prefixChanged(noteNum, value);
    } else if (column == 2) {
        emit suffixChanged(noteNum, value);
    }
}

int PrefixMapTab::convertToneToRow(int noteNum) const {
    int bottom = TONE_NUMBER_BASE;
    int countRow = mapTable->rowCount();

    return (countRow - 1) - (noteNum - bottom);
}

int PrefixMapTab::convertRowToTone(int row) const {
    int bottom = TONE_NUMBER_BASE;
    int countRow = mapTable->rowCount();
    return (countRow - 1) - (row - bottom);
}
