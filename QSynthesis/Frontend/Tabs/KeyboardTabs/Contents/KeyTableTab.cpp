#include "KeyTableTab.h"

#include <QAction>

KeyTableTab::KeyTableTab(TabWidget *parent) : BaseTab(parent) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);

    table = new QTableWidget();
    table->setProperty("type", "keyboard");

    QStringList header{tr("Command"), tr("Key Bind"), tr("Source")};

    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(header);
    table->horizontalHeader()->setDisabled(true);
    table->horizontalHeader()->setHighlightSections(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table->setAlternatingRowColors(true);

    mainLayout->addWidget(table);
    setLayout(mainLayout);
}

KeyTableTab::~KeyTableTab() {
}

void KeyTableTab::addActionData(QAction *action) {
    int row = table->rowCount();
    table->insertRow(row);

    QTableWidgetItem *item;

    item = new QTableWidgetItem(action->data().toString());
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    table->setItem(row, 0, item);

    item = new QTableWidgetItem(action->shortcut().toString());
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    table->setItem(row, 1, item);

    item = new QTableWidgetItem(tr("Default"));
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    table->setItem(row, 2, item);
}
