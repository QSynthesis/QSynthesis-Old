#include "../../Areas/Editor/NotesArea.h"
#include "../../TuningGroup.h"
#include "../EditorForm.h"
#include "Templates/TemporaryMenu.h"
#include "mainwindow.h"

void EditorForm::handleMenuBtnClicked() {
    QMenu *adsorbMenu = new QMenu(tr("Quantization"), m_menu);

    QAction *fullAdsorbAction = new QAction(tr("Quarter"), m_menu);
    QAction *halfAdsorbAction = new QAction(tr("1/2 Quarter"), m_menu);
    QAction *quarterAdsorbAction = new QAction(tr("1/4 Quarter"), m_menu);
    QAction *sixthAdsorbAction = new QAction(tr("1/6 Quarter"), m_menu);
    QAction *eighthAdsorbAction = new QAction(tr("1/8 Quarter"), m_menu);
    QAction *twelfthAdsorbAction = new QAction(tr("1/12 Quarter"), m_menu);
    QAction *sixteenthAdsorbAction = new QAction(tr("1/16 Quarter"), m_menu);
    QAction *twentyForthAdsorbAction = new QAction(tr("1/24 Quarter"), m_menu);
    QAction *thirtySecondAdsorbAction = new QAction(tr("1/32 Quarter"), m_menu);
    QAction *noAdsorbAction = new QAction(tr("None"), m_menu);

    fullAdsorbAction->setCheckable(true);
    halfAdsorbAction->setCheckable(true);
    quarterAdsorbAction->setCheckable(true);
    sixthAdsorbAction->setCheckable(true);
    eighthAdsorbAction->setCheckable(true);
    twelfthAdsorbAction->setCheckable(true);
    sixteenthAdsorbAction->setCheckable(true);
    twentyForthAdsorbAction->setCheckable(true);
    thirtySecondAdsorbAction->setCheckable(true);
    noAdsorbAction->setCheckable(true);

    connect(fullAdsorbAction, &QAction::triggered, this, &EditorForm::handleFullAdsorb);
    connect(halfAdsorbAction, &QAction::triggered, this, &EditorForm::handleHalfAdsorb);
    connect(quarterAdsorbAction, &QAction::triggered, this, &EditorForm::handleQuarterAdsorb);
    connect(sixthAdsorbAction, &QAction::triggered, this, &EditorForm::handleSixthAdsorb);
    connect(eighthAdsorbAction, &QAction::triggered, this, &EditorForm::handleEighthAdsorb);
    connect(twelfthAdsorbAction, &QAction::triggered, this, &EditorForm::handleTwelfthAdsorb);
    connect(sixteenthAdsorbAction, &QAction::triggered, this, &EditorForm::handleSixteenthAdsorb);
    connect(twentyForthAdsorbAction, &QAction::triggered, this,
            &EditorForm::handleTwentyForthAdsorb);
    connect(thirtySecondAdsorbAction, &QAction::triggered, this,
            &EditorForm::handleThirtySecondAdsorb);
    connect(noAdsorbAction, &QAction::triggered, this, &EditorForm::handleNoneAdsorb);

    switch (m_ptrs->currentAdsorb) {
    case 1:
        fullAdsorbAction->setChecked(true);
        break;
    case 2:
        halfAdsorbAction->setChecked(true);
        break;
    case 4:
        quarterAdsorbAction->setChecked(true);
        break;
    case 6:
        sixthAdsorbAction->setChecked(true);
        break;
    case 8:
        eighthAdsorbAction->setChecked(true);
        break;
    case 12:
        twelfthAdsorbAction->setChecked(true);
        break;
    case 16:
        sixteenthAdsorbAction->setChecked(true);
        break;
    case 24:
        twentyForthAdsorbAction->setChecked(true);
        break;
    case 32:
        thirtySecondAdsorbAction->setChecked(true);
        break;
    case 0:
        noAdsorbAction->setChecked(true);
        break;
    default:
        break;
    }

    adsorbMenu->addAction(fullAdsorbAction);
    adsorbMenu->addAction(halfAdsorbAction);
    adsorbMenu->addAction(quarterAdsorbAction);
    adsorbMenu->addAction(sixteenthAdsorbAction);
    adsorbMenu->addAction(eighthAdsorbAction);
    adsorbMenu->addAction(twelfthAdsorbAction);
    adsorbMenu->addAction(sixteenthAdsorbAction);
    adsorbMenu->addAction(twentyForthAdsorbAction);
    adsorbMenu->addAction(thirtySecondAdsorbAction);
    adsorbMenu->addSeparator();
    adsorbMenu->addAction(noAdsorbAction);

    m_menu->addMenu(adsorbMenu);
    m_menu->exec(QCursor::pos());
    m_menu->clear();
}

void EditorForm::handleFullAdsorb() {
    setLengthUnit(1);
}
void EditorForm::handleHalfAdsorb() {
    setLengthUnit(2);
}
void EditorForm::handleQuarterAdsorb() {
    setLengthUnit(4);
}
void EditorForm::handleSixthAdsorb() {
    setLengthUnit(6);
}
void EditorForm::handleEighthAdsorb() {
    setLengthUnit(8);
}
void EditorForm::handleTwelfthAdsorb() {
    setLengthUnit(12);
}
void EditorForm::handleSixteenthAdsorb() {
    setLengthUnit(16);
}
void EditorForm::handleTwentyForthAdsorb() {
    setLengthUnit(24);
}
void EditorForm::handleThirtySecondAdsorb() {
    setLengthUnit(32);
}
void EditorForm::handleNoneAdsorb() {
    setLengthUnit(0);
}

void EditorForm::setLengthUnit(int n) {
    m_ptrs->currentAdsorb = n;
    m_ptrs->notesArea->updateBackground();

    MainWindow::settingIni.lastQuantize = n;
}
