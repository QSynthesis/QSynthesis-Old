#include "../../Areas/Editor/NotesArea.h"
#include "../../TuningGroup.h"
#include "../EditorForm.h"
#include "Templates/TemporaryMenu.h"

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
    m_ptrs->currentAdsorb = n * 4;
    m_ptrs->notesArea->updateBackground();
}
