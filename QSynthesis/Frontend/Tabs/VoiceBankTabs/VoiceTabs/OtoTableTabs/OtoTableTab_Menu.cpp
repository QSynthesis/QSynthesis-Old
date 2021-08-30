#include "../OtoTableTab.h"

#include <QAction>
#include <QMenu>

void OtoTableTab::openContextMenu() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }

    QGenonSettings genon = getGenonSettings(row);

    QAction *playAction = new QAction(tr("Play"), m_menu);
    QAction *moveUpAction = new QAction(tr("Move up"), m_menu);
    QAction *moveDownAction = new QAction(tr("Move down"), m_menu);
    QAction *moveTopAction = new QAction(tr("Move to top"), m_menu);
    QAction *moveBottomAction = new QAction(tr("Move to bottom"), m_menu);
    QAction *duplicateAction = new QAction(tr("Duplicate"), m_menu);
    QAction *removeAction = new QAction(tr("Remove"), m_menu);

#if defined(_WIN32)
    QAction *revealAction = new QAction(tr("Show in Explorer(&S)"), m_menu);
#elif defined(__APPLE__)
    QAction *revealAction = new QAction(tr("Show in Finder(&S)"), m_menu);
#else
    QAction *revealAction = new QAction(tr("Show in File Manager(&S)"), m_menu);
#endif

    connect(playAction, &QAction::triggered, this, &OtoTableTab::handlePlayTriggered);
    connect(moveUpAction, &QAction::triggered, this, &OtoTableTab::handleMoveUpTriggered);
    connect(moveDownAction, &QAction::triggered, this, &OtoTableTab::handleMoveDownTriggered);
    connect(moveTopAction, &QAction::triggered, this, &OtoTableTab::handleMoveTopTriggered);
    connect(moveBottomAction, &QAction::triggered, this, &OtoTableTab::handleMoveBottomTriggered);
    connect(duplicateAction, &QAction::triggered, this, &OtoTableTab::handleDuplicateTriggered);
    connect(removeAction, &QAction::triggered, this, &OtoTableTab::handleRemoveTriggered);
    connect(revealAction, &QAction::triggered, this, &OtoTableTab::handleRevealTriggered);

    m_menu->addAction(playAction);
    m_menu->addAction(revealAction);
    m_menu->addSeparator();
    m_menu->addAction(moveUpAction);
    m_menu->addAction(moveDownAction);
    m_menu->addAction(moveTopAction);
    m_menu->addAction(moveBottomAction);
    m_menu->addSeparator();
    m_menu->addAction(duplicateAction);
    m_menu->addAction(removeAction);

    bool isTop = false;
    bool isBottom = false;

    if (row == 0 || fileNameAtRow(row) != fileNameAtRow(row - 1)) {
        moveUpAction->setEnabled(false);
        moveTopAction->setEnabled(false);
        isTop = true;
    }
    if (row == otoTable->rowCount() - 1 || fileNameAtRow(row) != fileNameAtRow(row + 1)) {
        moveDownAction->setEnabled(false);
        moveBottomAction->setEnabled(false);
        isBottom = true;
    }
    if (isTop && isBottom && genon.valid()) {
        removeAction->setEnabled(false);
    }
    if (!genon.valid()) {
        playAction->setEnabled(false);
        revealAction->setEnabled(false);
    }

    m_menu->exec(QCursor::pos());
    m_menu->clear();
}

void OtoTableTab::handlePlayTriggered() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }
    playSound(row);
}

void OtoTableTab::handleMoveUpTriggered() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    int firstRow = findFirstRow(genon.mFileName);
    int index = row - firstRow;
    int sequence = otoSamples.findAuto(genon.mFileName);

    genon = otoSamples.at(sequence).at(index);
    moveSample(row, sequence, index, -1);
    emit sampleMoved(genon, index, -1);
}

void OtoTableTab::handleMoveDownTriggered() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    int firstRow = findFirstRow(genon.mFileName);
    int index = row - firstRow;
    int sequence = otoSamples.findAuto(genon.mFileName);

    genon = otoSamples.at(sequence).at(index);
    moveSample(row, sequence, index, 1);
    emit sampleMoved(genon, index, 1);
}

void OtoTableTab::handleMoveTopTriggered() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    int firstRow = findFirstRow(genon.mFileName);
    int index = row - firstRow;
    int sequence = otoSamples.findAuto(genon.mFileName);
    int movement = -index;

    genon = otoSamples.at(sequence).at(index);
    moveSample(row, sequence, index, movement);
    emit sampleMoved(genon, index, movement);
}

void OtoTableTab::handleMoveBottomTriggered() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    int firstRow = findFirstRow(genon.mFileName);
    int index = row - firstRow;
    int sequence = otoSamples.findAuto(genon.mFileName);
    int movement = otoSamples.at(sequence).size() - 1 - index;

    genon = otoSamples.at(sequence).at(index);
    moveSample(row, sequence, index, movement);
    emit sampleMoved(genon, index, movement);
}

void OtoTableTab::handleDuplicateTriggered() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    int firstRow = findFirstRow(genon.mFileName);
    int index = row - firstRow;
    int sequence = otoSamples.findAuto(genon.mFileName);

    genon = otoSamples.at(sequence).at(index);
    otoSamples[sequence].insert(index + 1, genon);

    otoTable->blockSignals(true);
    insertRow(row + 1, genon);
    selectRow(row + 1);
    otoTable->blockSignals(false);

    emit sampleAdded(genon, index + 1);
}

void OtoTableTab::handleRemoveTriggered() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    int firstRow = findFirstRow(genon.mFileName);
    int index = row - firstRow;
    int sequence = otoSamples.findAuto(genon.mFileName);

    genon = otoSamples.at(sequence).at(index);

    // Change backend value
    if (otoSamples[sequence].size() == 1) {
        validCache.remove(otoSamples[sequence].filename());
        otoSamples.removeAt(sequence);
    } else {
        otoSamples[sequence].removeAt(index);
    }

    otoTable->blockSignals(true);
    removeRow(row);
    selectNone();
    sendNoneToVision();
    otoTable->blockSignals(false);

    emit sampleRemoved(genon, index);
}

void OtoTableTab::handleRevealTriggered() {
    int row = otoTable->currentRow();
    if (row < 0 || row >= otoTable->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    RevealFile(genon.mFileName);
}
