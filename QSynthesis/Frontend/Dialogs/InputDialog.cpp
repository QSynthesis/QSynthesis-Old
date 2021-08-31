#include "InputDialog.h"

InputDialog::InputDialog(QString title, QString caption, double &value, QValidator *validator,
                         QWidget *parent)
    : BaseDialog(parent), orgValue(value), m_title(title), m_caption(caption), m_validator(validator) {
    init();
}

InputDialog::~InputDialog() {
}

int InputDialog::exec() {
    setResult(0);
    return QDialog::exec();
}

void InputDialog::init() {
    setWindowFlags(Qt::WindowCloseButtonHint);

    setWindowTitle(m_title);
    setFixedSize(450, 200);

    // 添加标签和按钮
    QFont font(mainFont());

    btnCancel = new QPushButton(tr("Cancel"), this);
    btnOK = new QPushButton(tr("OK"), this);

    lcInput = new LineControl(Qt::Vertical, m_caption, QString::number(orgValue), this);
    lcInput->setValidator(m_validator);

    // Initialize Properties
    btnCancel->setFont(font);
    btnOK->setFont(font);

    btnCancel->setFixedSize(115, 35);
    btnOK->setFixedSize(115, 35);

    btnOK->setDefault(true);

    lcInput->Text()->setFocus();

    btnOK->setShortcut(QKeySequence(Qt::Key_Return));
    btnCancel->setShortcut(QKeySequence(Qt::Key_Escape));

    connect(btnOK, &QPushButton::clicked, this, &InputDialog::onOKClicked);
    connect(btnCancel, &QPushButton::clicked, this, &InputDialog::onCancelClicked);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(20);

    buttonLayout = new QHBoxLayout();

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnOK);
    buttonLayout->addWidget(btnCancel);

    mainLayout->addStretch();
    mainLayout->addWidget(lcInput);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

void InputDialog::onOKClicked() {
    orgValue = lcInput->getValue().toDouble();
    setResult(1);
    close();
}

void InputDialog::onCancelClicked() {
    close();
}

void InputDialog::closeEvent(QCloseEvent *event) {
    event->accept();
}
