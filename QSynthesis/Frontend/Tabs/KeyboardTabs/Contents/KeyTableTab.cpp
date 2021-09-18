#include "KeyTableTab.h"

KeyTableTab::KeyTableTab(TabWidget *parent) : BaseTab(parent) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);

    table = new QTableWidget();
    table->setProperty("type", "keyboard");

    QStringList header{tr("Command"),tr("Shortcut"),tr("Source")};

    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(header);
    table->horizontalHeader()->setDisabled(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table->setAlternatingRowColors(true);

    mainLayout->addWidget(table);
    setLayout(mainLayout);
}

KeyTableTab::~KeyTableTab() {
}
