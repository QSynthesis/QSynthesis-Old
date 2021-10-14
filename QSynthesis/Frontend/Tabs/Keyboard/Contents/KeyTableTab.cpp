#include "KeyTableTab.h"
#include "../KeyboardTab.h"

#include <QAction>

KeyTableTab::KeyTableTab(KeyboardTab *tab, TabWidget *parent) : BaseTab(parent), m_tab(tab) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);

    table = new QTableWidget();

    table->installEventFilter(this);
    table->viewport()->installEventFilter(this);

    table->setProperty("type", "keyboard");

    QStringList header{tr("Command"), tr("Key Bind"), tr("Source")};

    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(header);
    table->horizontalHeader()->setDisabled(true);
    table->horizontalHeader()->setHighlightSections(false);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    //    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table->setAlternatingRowColors(true);

    setContextMenuPolicy(Qt::CustomContextMenu);

    mainLayout->addWidget(table);
    setLayout(mainLayout);

    connect(table, &QTableWidget::cellDoubleClicked, this, &KeyTableTab::handleCellDoubleClicked);
    connect(table, &QTableWidget::itemSelectionChanged, this, &KeyTableTab::handleSelectionChanged);
}

KeyTableTab::~KeyTableTab() {
}

void KeyTableTab::addShortcutData(QAction *action) {
    int row = table->rowCount();
    table->insertRow(row);

    for (int i = 0; i < 3; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(action->data().toString());
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        table->setItem(row, i, item);
    }

    setNameAtRow(row, action->data().toString());
    setShortcutAtRow(row, action->shortcut().toString());
}

void KeyTableTab::removeAllData() {
    for (int i = table->rowCount() - 1; i >= 0; --i) {
        table->removeRow(i);
    }
}

QList<QKeySequence> KeyTableTab::defaultShortcuts() const {
    return m_defaultShortcuts;
}

void KeyTableTab::setDefaultShortcuts(const QList<QKeySequence> &defaultShortcuts) {
    m_defaultShortcuts = defaultShortcuts;
}

QList<QKeySequence> KeyTableTab::currentShortcuts() const {
    QList<QKeySequence> shortcuts;
    for (int i = 0; i < table->rowCount(); ++i) {
        shortcuts.append(shortcutAtRow(i));
    }
    return shortcuts;
}

void KeyTableTab::selectAll() {
    table->selectAll();
}

void KeyTableTab::selectNone() {
    const QList<QTableWidgetSelectionRange> &ranges = table->selectedRanges();
    for (int i = 0; i < ranges.size(); ++i) {
        table->setRangeSelected(ranges.at(i), false);
    }
}

void KeyTableTab::selectRow(int row) {
    QTableWidgetItem *item = table->item(row, 0);
    table->scrollToItem(item);

    QTableWidgetSelectionRange range(row, 0, row, table->columnCount() - 1);
    table->setCurrentItem(item);
    table->setRangeSelected(range, true);
}

QList<QTableWidgetSelectionRange> KeyTableTab::selectedRanges() const {
    return table->selectedRanges();
}

QString KeyTableTab::nameAtRow(int row) const {
    return table->item(row, 0)->text();
}

QString KeyTableTab::shortcutAtRow(int row) const {
    return table->item(row, 1)->text();
}

Qs::VariableSource KeyTableTab::sourceAtRow(int row) const {
    QString text = table->item(row, 1)->text();
    return (QKeySequence(text) == m_defaultShortcuts.at(row)) ? Qs::Default : Qs::User;
}

void KeyTableTab::setNameAtRow(int row, const QString &name) {
    QTableWidgetItem *item = table->item(row, 0);
    item->setText(name);
}

void KeyTableTab::setShortcutAtRow(int row, const QString &text) {
    QTableWidgetItem *key = table->item(row, 1);
    QTableWidgetItem *source = table->item(row, 2);

    key->setText(text);
    source->setText((sourceAtRow(row) == Qs::Default) ? tr("Default") : tr("User"));
}

bool KeyTableTab::eventFilter(QObject *obj, QEvent *event) {
    if (obj == table->viewport()) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::RightButton) {
                int row = table->rowAt(mouseEvent->pos().y());
                if (row >= 0 && row < table->rowCount()) {
                    selectNone();
                    selectRow(row);
                    openContextMenu();
                    return true;
                }
            }
        }
    } else if (obj == table) {
        if (event->type() == QEvent::FocusOut) {
            // selectNone();
        }
    }
    return BaseTab::eventFilter(obj, event);
}
