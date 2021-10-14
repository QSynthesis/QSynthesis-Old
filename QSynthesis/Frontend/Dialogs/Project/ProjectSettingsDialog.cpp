#include "ProjectSettingsDialog.h"
#include "SettingIniFile.h"
#include "application.h"

#include <QFileDialog>
#include <QMessageBox>

ProjectSettingsDialog::ProjectSettingsDialog(QString &wavtool, QString &outfile, QString &cache,
                                             QWidget *parent)
    : BaseDialog(parent), wavtool(wavtool), outfile(outfile), cache(cache) {
    init();
}

ProjectSettingsDialog::~ProjectSettingsDialog() {
}

int ProjectSettingsDialog::exec() {
    return BaseDialog::exec();
}

void ProjectSettingsDialog::init() {
    setWindowTitle(tr("Project Settings"));
    setFixedSize(720, 350);

    // 添加标签和按钮
    btnCancel = new QPushButton(tr("Cancel"), this);
    btnOK = new QPushButton(tr("OK"), this);
    btnClear = new QPushButton(tr("Clear"), this);
    btnBrowse = new QPushButton(tr("Browse"), this);

    // Convert to native separators
    QStringList wavtools = qSetting->wavtools.valid();
    for (auto it = wavtools.begin(); it != wavtools.end(); ++it) {
        *it = QDir::toNativeSeparators(PathFindFileName(*it, AppPath));
    }

    ccWavtool = new ComboControl(Qt::Vertical, tr("Wavtool"), wavtools, this);
    lcOutfile = new LineControl(Qt::Vertical, tr("Output File Name"), outfile, this);
    lcCache = new LineControl(Qt::Vertical, tr("Cache Directory"), cache, this);

    ccWavtool->Combo()->setEditable(true);
    lcCache->Text()->setReadOnly(true);

    ccWavtool->Combo()->setCurrentText(
        QDir::toNativeSeparators(PathFindFileName(wavtool, AppPath)));

    btnCancel->setFixedSize(115, 35);
    btnOK->setFixedSize(115, 35);
    btnClear->setFixedSize(115, 35);
    btnBrowse->setFixedSize(115, 35);

    btnOK->setDefault(true);

    btnOK->setShortcut(QKeySequence(Qt::Key_Return));
    btnCancel->setShortcut(QKeySequence(Qt::Key_Escape));

    connect(btnOK, &QPushButton::clicked, this, &ProjectSettingsDialog::onOKClicked);
    connect(btnCancel, &QPushButton::clicked, this, &ProjectSettingsDialog::onCancelClicked);
    connect(btnClear, &QPushButton::clicked, this, &ProjectSettingsDialog::onClearBtnClicked);
    connect(btnBrowse, &QPushButton::clicked, this, &ProjectSettingsDialog::onBrowseBtnClicked);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(20);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnOK);
    buttonLayout->addWidget(btnCancel);

    browseLayout = new QHBoxLayout();
    browseLayout->addStretch();
    browseLayout->addWidget(btnClear);
    browseLayout->addWidget(btnBrowse);

    mainLayout->addStretch();
    mainLayout->addWidget(ccWavtool);
    mainLayout->addLayout(browseLayout);
    mainLayout->addWidget(lcOutfile);
    mainLayout->addWidget(lcCache);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

void ProjectSettingsDialog::onOKClicked() {
    QString temp = QDir::fromNativeSeparators(ccWavtool->Combo()->currentText());
    QFileInfo file(temp);

    if (!file.isFile()) {
        QMessageBox::warning(this, MainTitle, tr("Wavtool doesn't esist!"));
        return;
    }

    wavtool = file.absoluteFilePath();
    outfile = lcOutfile->getValue();
    cache = lcCache->getValue();

    qSetting->wavtools.advance(wavtool);

    setResult(1);
    close();
}

void ProjectSettingsDialog::onCancelClicked() {
    close();
}

void ProjectSettingsDialog::onClearBtnClicked() {
    ccWavtool->Combo()->clear();
    qSetting->wavtools.clear();
}

void ProjectSettingsDialog::onBrowseBtnClicked() {
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Set Wavtool"), ".", toolsFilterString);
    if (!path.isEmpty()) {
        ccWavtool->Combo()->setCurrentText(
            QDir::toNativeSeparators(PathFindFileName(path, AppPath)));
    }
}
