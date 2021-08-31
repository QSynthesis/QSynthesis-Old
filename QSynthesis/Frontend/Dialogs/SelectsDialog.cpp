#include "SelectsDialog.h"

SelectsDialog::SelectsDialog(const QString &title, const QString &caption, const QStringList &list,
                             QVector<bool> &result, bool single, QWidget *parent)
    : QDialog(parent), m_result(result), m_single(single), m_options(list), m_title(title),
      m_caption(caption) {
    init();
}

SelectsDialog::~SelectsDialog() {
}

int SelectsDialog::exec() {
    setResult(0);
    return QDialog::exec();
}

void SelectsDialog::init() {
    setWindowFlags(Qt::WindowCloseButtonHint);

    setWindowTitle(m_title);

    // 添加标签和按钮
    QFont font(mainFont());

    lbCaption = new QLabel(m_caption, this);

    btnCancel = new QPushButton(tr("Cancel"), this);
    btnOK = new QPushButton(tr("OK"), this);

    for (auto it = m_options.begin(); it != m_options.end(); ++it) {
        QCheckBox *box = new QCheckBox(*it, this);
        boxes.append(box);
    }

    if (m_single) {
        for (int i = 0; i < boxes.size(); ++i) {
            boxes.at(i)->setAutoExclusive(true);
        }
    }

    // Initialize Properties
    lbCaption->setFont(font);
    btnCancel->setFont(font);
    btnOK->setFont(font);

    btnCancel->setFixedSize(115, 35);
    btnOK->setFixedSize(115, 35);

    btnOK->setFocus();
    btnOK->setDefault(true);

    btnOK->setShortcut(QKeySequence(Qt::Key_Return));
    btnCancel->setShortcut(QKeySequence(Qt::Key_Escape));

    connect(btnOK, &QPushButton::clicked, this, &SelectsDialog::onOKClicked);
    connect(btnCancel, &QPushButton::clicked, this, &SelectsDialog::onCancelClicked);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(20);

    buttonLayout = new QHBoxLayout();

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnOK);
    buttonLayout->addWidget(btnCancel);

    mainLayout->addStretch();
    mainLayout->addWidget(lbCaption);

    for (int i = 0; i < boxes.size(); ++i) {
        mainLayout->addWidget(boxes.at(i));
    }

    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    adjustSize();
    setFixedSize(size().width() < 450 ? 450 : size().width(), size().height());
}

void SelectsDialog::onOKClicked() {
    bool isChecked = false;
    m_result.clear();
    for (int i = 0; i < boxes.size(); ++i) {
        if (boxes.at(i)->isChecked()) {
            isChecked = true;
        }
        m_result.append(boxes.at(i)->isChecked());
    }

    if (!isChecked) {
        QMessageBox::warning(this, MainTitle, tr("Please select at least one!"));
        return;
    }

    setResult(1);
    close();
}

void SelectsDialog::onCancelClicked() {
    close();
}

void SelectsDialog::closeEvent(QCloseEvent *event) {
    event->accept();
}
