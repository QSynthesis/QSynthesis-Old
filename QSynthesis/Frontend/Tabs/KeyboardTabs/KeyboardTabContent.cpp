#include "KeyboardTabContent.h"

KeyboardTabContent::KeyboardTabContent(KeyboardTab *tab, QWidget *parent)
    : QWidget(parent), m_tab(tab) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(40);
    mainLayout->setSpacing(10);

    //添加过滤器
    filterEdit = new QLineEdit();
    filterEdit->setPlaceholderText("Type to search in keybindings");
    filterEdit->setFixedHeight(30);
    mainLayout->addWidget(filterEdit);

    connect(filterEdit, &FixedLineEdit::textChanged, this, &KeyboardTabContent::filterRows);

    //添加映射列表
    tableWidget = new KeyTableWidget(this);
    mainLayout->addWidget(tableWidget);

    setLayout(mainLayout);
    setAutoFillBackground(true);
}

void KeyboardTabContent::focusInEvent(QFocusEvent *e) {
    QPalette p;
    p.setColor(QPalette::Window, Qt::red);
    setPalette(p);
}

void KeyboardTabContent::focusOutEvent(QFocusEvent *e) {
    QPalette p;
    p.setColor(QPalette::Window, Qt::white);
    setPalette(p);
}

void KeyboardTabContent::filterRows(const QString &text) {
    QTableWidget *table = tableWidget->table();
    bool bRowHidden = true;
    for (int i = 0; i < table->rowCount(); ++i) {
        bRowHidden = true;
        for (int j = 1; j < table->columnCount(); ++j) {
            QString contents = tableWidget->data().at(i).at(j - 1);
            KeyLabelContent *newLable = new KeyLabelContent();
            newLable->setAttribute(Qt::WA_TransparentForMouseEvents, true);
            if (contents.contains(text, Qt::CaseInsensitive)) {
                if (!text.isEmpty()) {
                    int textLen = text.length();
                    int index = contents.indexOf(text, 0, Qt::CaseInsensitive);
                    while (index != -1) {
                        QString originText = contents.mid(index, textLen);
                        QString newText = "<html><font color=red>" + originText + "</font></html>";
                        contents.replace(index, textLen, newText);
                        index += newText.length();
                        index = contents.indexOf(text, index, Qt::CaseInsensitive);
                    }
                }
                bRowHidden = false;
            }
            newLable->setText(contents);
            table->setCellWidget(i, j, newLable);
        }
        table->setRowHidden(i, bRowHidden);
    }
}
