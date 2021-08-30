#include "KeyTableWidget.h"

KeyTableWidget::KeyTableWidget(QWidget *parent) : QWidget(parent) {
    setFocusPolicy(Qt::ClickFocus);
    mainLayout = new QVBoxLayout();

    myTable = new QTableWidget();
    myTable->setColumnCount(4);
    QStringList header;

    header.append({tr(""), tr("Command"), tr("Key"), tr("Source")});

    myTable->setHorizontalHeaderLabels(header);
    myTable->verticalHeader()->setVisible(false);
    myTable->horizontalHeader()->setSectionsClickable(false);
    myTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    myTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //设置单元格整行选中，不可Edit
    myTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    myTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    myTable->setSelectionMode(QAbstractItemView::SingleSelection);
    myTable->setFocusPolicy(Qt::NoFocus);

    //设置表格整体样式
    myTable->setShowGrid(false);
    //鼠标悬停效果
    myTable->setMouseTracking(true);
    preRow = -1;
    preColor = QColor(255, 255, 255);

    //绑定事件
    mainLayout->addWidget(myTable);
    setLayout(mainLayout);
    connect(myTable, &QTableWidget::cellEntered, this, &KeyTableWidget::onCellEntered);
    connect(myTable, &QTableWidget::cellDoubleClicked, this, &KeyTableWidget::onDoubleClicked);

    editIcon = createBitmapFromSVG_W(":/images/Pencil.svg", QSize(32, 32), Qt::black);
}

bool KeyTableWidget::load(const ShortcutsData &keys) {
    dataList.clear();

    ShortcutsData defaultKeys;
    for (int i = ShortcutsData::idStart(); i < ShortcutsData::idEnd();
         ++i) {
        // get string
        QString command = keys.nameForId(i);
        QKeySequence key = keys.keyForId(i).toString();

        QString strKey = key.toString();
        QString source = (key == defaultKeys.keyForId(i)) ? tr("Default") : tr("User");

        // new widget.
        KeyLabelContent *editBtn = new KeyLabelContent("");
        KeyLabelContent *commandLable = new KeyLabelContent(command);
        KeyLabelContent *keyLable = new KeyLabelContent(strKey);
        KeyLabelContent *sourceLable = new KeyLabelContent(source);

        editBtn->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        commandLable->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        keyLable->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        sourceLable->setAttribute(Qt::WA_TransparentForMouseEvents, true);

        // insert new row.
        int row = myTable->rowCount();
        myTable->insertRow(row);
        myTable->setCellWidget(row, 0, editBtn);
        myTable->setCellWidget(row, 1, commandLable);
        myTable->setCellWidget(row, 2, keyLable);
        myTable->setCellWidget(row, 3, sourceLable);

        dataList.append({command, strKey, source});
    }
    return true;
}

void KeyTableWidget::setRowColor(int row, QColor color, bool in) {
    if (in) {
        QPushButton *rowEditBtn = new QPushButton;
        rowEditBtn->setStyleSheet("border:none;");
        rowEditBtn->setIcon(QIcon(editIcon));
        connect(rowEditBtn, &QPushButton::clicked, this, [=]() { onDoubleClicked(row); });
        myTable->setCellWidget(row, 0, rowEditBtn);
    } else {
        KeyLabelContent *editBtn = new KeyLabelContent("");
        editBtn->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        myTable->setCellWidget(row, 0, editBtn);
    }
    for (int column = 0; column < myTable->columnCount(); ++column) {
        QWidget *cell = myTable->cellWidget(row, column);
        QString color_str = "background-color:rgb(";
        color_str += QString::number(color.red()) + ',';
        color_str += QString::number(color.green()) + ',';
        color_str += QString::number(color.blue()) + ')';
        cell->setStyleSheet(color_str);
    }
}

QTableWidget *KeyTableWidget::table() {
    return myTable;
}

QVector<QStringList> &KeyTableWidget::data() {
    return dataList;
}

void KeyTableWidget::leaveEvent(QEvent *e) {
    //还原上一行的颜色
    QWidget *thisCell = myTable->cellWidget(preRow, 0);
    if (thisCell) {
        setRowColor(preRow, QColor(255, 255, 255), false);
    }
}

void KeyTableWidget::onCellEntered(int row, int column) {
    if (row == preRow) {
        return;
    }

    QWidget *preCell = myTable->cellWidget(preRow, column);
    if (preCell) {
        this->setRowColor(preRow, QColor(255, 255, 255), false);
    }

    preRow = row;
    QWidget *thisCell = myTable->cellWidget(row, column);
    if (thisCell) {
        this->setRowColor(row, QColor(232, 232, 232), true);
    }
}

void KeyTableWidget::onDoubleClicked(int row) {
    KeyModifyWidget *edit = new KeyModifyWidget(this);

    int code = edit->exec();
    QString text = edit->text();
    delete edit;

    if (code == 1) {
        setKey(row, text);
        emit keyModified(row, text);
    }
}

void KeyTableWidget::setKey(int id, QString key) {
    KeyLabelContent *keyLabel = new KeyLabelContent(key);
    keyLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    myTable->setCellWidget(id, 2, keyLabel);
    dataList[id][1] = key;

    ShortcutsData defaultKeys;
    QString source = (QKeySequence(key) == defaultKeys.keyForId(id)) ? tr("Default") : tr("User");

    KeyLabelContent *sourceLabel = new KeyLabelContent(source);
    keyLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    myTable->setCellWidget(id, 3, sourceLabel);
    dataList[id][2] = source;
}
