#include "NotePropertiesDialog.h"

using namespace Utau;

#include <cmath>

NotePropertiesDialog::NotePropertiesDialog(NoteProperties &np, int count,QWidget *parent)
    : BaseDialog(parent), orgValues(np), count(count) {
    init();
}

NotePropertiesDialog::~NotePropertiesDialog() {
}

int NotePropertiesDialog::exec() {
    setResult(0);
    return BaseDialog::exec();
}

void NotePropertiesDialog::init() {
    // 窗口初始化
    setWindowTitle(tr("Note Properties"));
    setFixedSize(450, 600);

    // 添加标签和按钮
    btnCancel = new QPushButton(tr("Cancel"), this);
    btnOK = new QPushButton(tr("OK"), this);

    scIntensity = new SlideLineControl(tr("Intensity"), this);
    scModulation = new SlideLineControl(tr("Modulation"), this);

    tcFlags = new LineControl(Qt::Horizontal, tr("Flags"), this);
    tcPreUtterance = new LineControl(Qt::Horizontal, tr("PreUtterance"), this);
    tcOverlap = new LineControl(Qt::Horizontal, tr("Overlap"), this);
    tcLength = new LineControl(Qt::Horizontal, tr("Length"), this);
    tcVelocity = new LineControl(Qt::Horizontal, tr("Consonant Velocity"), this);
    tcStartPoint = new LineControl(Qt::Horizontal, tr("Start Point"), this);

    btnCancel->setFixedSize(115, 35);
    btnOK->setFixedSize(115, 35);

    btnOK->setFocus();
    btnOK->setDefault(true);

    btnOK->setShortcut(QKeySequence(Qt::Key_Return));
    btnCancel->setShortcut(QKeySequence(Qt::Key_Escape));

    connect(btnOK, &QPushButton::clicked, this, &NotePropertiesDialog::onOKClicked);
    connect(btnCancel, &QPushButton::clicked, this, &NotePropertiesDialog::onCancelClicked);

    tcFlags->setProportion(1, 2);
    tcPreUtterance->setProportion(1, 1);
    tcOverlap->setProportion(1, 1);
    tcLength->setProportion(1, 1);
    tcVelocity->setProportion(1, 1);
    tcStartPoint->setProportion(1, 1);

    scIntensity->setFixedHeight(100);
    scModulation->setFixedHeight(100);

    tcFlags->setFixedHeight(50);
    tcPreUtterance->setFixedHeight(50);
    tcOverlap->setFixedHeight(50);
    tcLength->setFixedHeight(50);
    tcVelocity->setFixedHeight(50);
    tcStartPoint->setFixedHeight(50);

    scIntensity->setProportion(1, 1);
    scIntensity->setSingleStep(0.01);
    scIntensity->setBlankValue(DEFAULT_VALUE_INTENSITY);
    scIntensity->setMinimum(0);   // Minimum 0
    scIntensity->setMaximum(200); // Maximum 200

    scModulation->setProportion(1, 1);
    scModulation->setSingleStep(0.01);
    scModulation->setBlankValue(DEFAULT_VALUE_MODULATION);
    scModulation->setMinimum(-200); // Minimum -200
    scModulation->setMaximum(200);  // Maximum 200

    // 设置删除按钮可见
    scIntensity->Text()->setClearButtonEnabled(true);
    scModulation->Text()->setClearButtonEnabled(true);
    tcFlags->Text()->setClearButtonEnabled(true);
    tcPreUtterance->Text()->setClearButtonEnabled(true);
    tcOverlap->Text()->setClearButtonEnabled(true);
    tcVelocity->Text()->setClearButtonEnabled(true);
    tcStartPoint->Text()->setClearButtonEnabled(true);
    tcLength->Text()->setClearButtonEnabled(true);

    // 添加限制数字
    QDoubleValidator *dblValidatorP = new QDoubleValidator(0, INFINITY, 3, this);
    QDoubleValidator *dblValidatorR = new QDoubleValidator(-INFINITY, INFINITY, 3, this);
    QDoubleValidator *dblValidatorL = new QDoubleValidator(15, INFINITY, 0, this);

    dblValidatorP->setNotation(QDoubleValidator::StandardNotation);
    dblValidatorR->setNotation(QDoubleValidator::StandardNotation);
    dblValidatorL->setNotation(QDoubleValidator::StandardNotation);

    tcPreUtterance->setValidator(dblValidatorP);
    tcOverlap->setValidator(dblValidatorR);
    tcLength->setValidator(dblValidatorL);
    tcVelocity->setValidator(dblValidatorR);
    tcStartPoint->setValidator(dblValidatorP);

    // Initialize layouts
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(20);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnOK);
    buttonLayout->addWidget(btnCancel);

    mainLayout->addWidget(tcLength);
    mainLayout->addWidget(tcPreUtterance);
    mainLayout->addWidget(tcOverlap);
    mainLayout->addWidget(tcVelocity);
    mainLayout->addWidget(tcStartPoint);
    mainLayout->addWidget(scIntensity);
    mainLayout->addWidget(scModulation);
    mainLayout->addWidget(tcFlags);
    mainLayout->addLayout(buttonLayout);

    SetCurrentValues();
}


void NotePropertiesDialog::onOKClicked() {
    SaveCurrentValues();
    setResult(1);
    close();
}

void NotePropertiesDialog::onCancelClicked() {
    close();
}

void NotePropertiesDialog::SetCurrentValues() {
    // Len
    if (orgValues.length == NODEF_STRING) {
        tcLength->setValue(ambiguousValue);
        tcLength->setUnmodified(true);
    } else {
        tcLength->setValue(orgValues.length);
    }

    // Int
    if (orgValues.intensity == NODEF_STRING) {
        scIntensity->setText(ambiguousValue);
        scIntensity->setUnmodified(true);
    } else {
        scIntensity->setText(orgValues.intensity);
    }

    // Mod
    if (orgValues.modulation == NODEF_STRING) {
        scModulation->setText(ambiguousValue);
        scModulation->setUnmodified(true);
    } else {
        scModulation->setText(orgValues.modulation);
    }

    // Pre
    if (orgValues.preUttr == NODEF_STRING) {
        tcPreUtterance->setValue(ambiguousValue);
        tcPreUtterance->setUnmodified(true);
    } else {
        tcPreUtterance->setValue(orgValues.preUttr);
    }

    // Ove
    if (orgValues.overlap == NODEF_STRING) {
        tcOverlap->setValue(ambiguousValue);
        tcOverlap->setUnmodified(true);
    } else {
        tcOverlap->setValue(orgValues.overlap);
    }

    // Vel
    if (orgValues.velocity == NODEF_STRING) {
        tcVelocity->setValue(ambiguousValue);
        tcVelocity->setUnmodified(true);
    } else {
        tcVelocity->setValue(orgValues.velocity);
    }

    // Stp
    if (orgValues.startpoint == NODEF_STRING) {
        tcStartPoint->setValue(ambiguousValue);
        tcStartPoint->setUnmodified(true);
    } else {
        tcStartPoint->setValue(orgValues.startpoint);
    }

    // Flags
    if (orgValues.flags == NODEF_STRING) {
        tcFlags->setValue(ambiguousValue);
        tcFlags->setUnmodified(true);
    } else {
        tcFlags->setValue(orgValues.flags);
    }

    // Set placeholder
    if (count == 1) {
        if (orgValues.preUttrOto == NODEF_STRING) {
            tcPreUtterance->setPlaceholder(tr("Not found"), ambiguousValue);
            tcOverlap->setPlaceholder(tr("Not found"), ambiguousValue);
        } else {
            tcPreUtterance->setPlaceholder(orgValues.preUttrOto, ambiguousValue);
            tcOverlap->setPlaceholder(orgValues.overlapOto, ambiguousValue);
        }
    } else {
        tcPreUtterance->setPlaceholder(tr("oto"), ambiguousValue);
        tcOverlap->setPlaceholder(tr("oto"), ambiguousValue);
    }

    scIntensity->setPlaceholder(QString::number(DEFAULT_VALUE_INTENSITY), ambiguousValue);
    scModulation->setPlaceholder(QString::number(DEFAULT_VALUE_MODULATION), ambiguousValue);
    tcVelocity->setPlaceholder(QString::number(DEFAULT_VALUE_VELOCITY), ambiguousValue);
    tcStartPoint->setPlaceholder(QString::number(DEFAULT_VALUE_START_POINT), ambiguousValue);
}

void NotePropertiesDialog::SaveCurrentValues() {
    if (!tcLength->unmodified()) {
        orgValues.length = tcLength->getValue();
    }
    if (!scIntensity->unmodified()) {
        orgValues.intensity = scIntensity->getText();
    }
    if (!scModulation->unmodified()) {
        orgValues.modulation = scModulation->getText();
    }
    if (!tcPreUtterance->unmodified()) {
        orgValues.preUttr = tcPreUtterance->getValue();
    }
    if (!tcOverlap->unmodified()) {
        orgValues.overlap = tcOverlap->getValue();
    }
    if (!tcVelocity->unmodified()) {
        orgValues.velocity = tcVelocity->getValue();
    }
    if (!tcStartPoint->unmodified()) {
        orgValues.startpoint = tcStartPoint->getValue();
    }
    if (!tcFlags->unmodified()) {
        orgValues.flags = tcFlags->getValue();
    }
}
