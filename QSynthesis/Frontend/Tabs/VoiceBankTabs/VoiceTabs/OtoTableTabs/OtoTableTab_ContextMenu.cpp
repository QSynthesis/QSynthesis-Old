#include "../OtoTableTab.h"

#include <QAction>
#include <QMenu>

void OtoTableTab::openContextMenu() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
        return;
    }

    QAction *playAction = new QAction(tr("Play"), m_menu);
    QAction *moveUpAction = new QAction(tr("Move up"), m_menu);
    QAction *moveDownAction = new QAction(tr("Move down"), m_menu);
    QAction *moveTopAction = new QAction(tr("Move to top"), m_menu);
    QAction *moveBottomAction = new QAction(tr("Move to bottom"), m_menu);
    QAction *duplicateAction = new QAction(tr("Duplicate"), m_menu);
    QAction *removeAction = new QAction(tr("Remove"), m_menu);

#if defined(Q_OS_WINDOWS)
    QAction *revealAction = new QAction(tr("Show in Explorer(&S)"), m_menu);
#elif defined(Q_OS_MAC)
    QAction *revealAction = new QAction(tr("Show in Finder(&S)"), m_menu);
#else
    QAction *revealAction = new QAction(tr("Show in File Manager(&S)"), m_menu);
#endif

    connect(playAction, &QAction::triggered, this, &OtoTableTab::play);
    connect(moveUpAction, &QAction::triggered, this, &OtoTableTab::moveUp);
    connect(moveDownAction, &QAction::triggered, this, &OtoTableTab::moveDown);
    connect(moveTopAction, &QAction::triggered, this, &OtoTableTab::moveTop);
    connect(moveBottomAction, &QAction::triggered, this, &OtoTableTab::moveBottom);
    connect(duplicateAction, &QAction::triggered, this, &OtoTableTab::duplicate);
    connect(removeAction, &QAction::triggered, this, &OtoTableTab::remove);
    connect(revealAction, &QAction::triggered, this, &OtoTableTab::reveal);

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

    bool isTop = isCurrentTop();
    bool isBottom = isCurrentBottom();
    bool isValid = isCurrentValid();

    if (isTop) {
        moveUpAction->setEnabled(false);
        moveTopAction->setEnabled(false);
    }
    if (isBottom) {
        moveDownAction->setEnabled(false);
        moveBottomAction->setEnabled(false);
    }
    if (isTop && isBottom && isValid) {
        removeAction->setEnabled(false);
    }
    if (!isValid) {
        playAction->setEnabled(false);
        revealAction->setEnabled(false);
    }

    m_menu->exec(QCursor::pos());
    m_menu->clear();
}

void OtoTableTab::play() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
        return;
    }
    playSound(row);
}

void OtoTableTab::moveUp() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
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

void OtoTableTab::moveDown() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
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

void OtoTableTab::moveTop() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
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

void OtoTableTab::moveBottom() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
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

void OtoTableTab::duplicate() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    int firstRow = findFirstRow(genon.mFileName);
    int index = row - firstRow;
    int sequence = otoSamples.findAuto(genon.mFileName);

    genon = otoSamples.at(sequence).at(index);
    otoSamples[sequence].insert(index + 1, genon);

    table->blockSignals(true);
    insertRow(row + 1, genon);

    selectNone();
    selectRow(row + 1);
    table->blockSignals(false);

    emit sampleAdded(genon, index + 1);
}

void OtoTableTab::remove() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
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

    table->blockSignals(true);
    removeRow(row);
    selectNone();
    sendNoneToVision();
    table->blockSignals(false);

    emit sampleRemoved(genon, index);
}

void OtoTableTab::reveal() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
        return;
    }
    QGenonSettings genon = getGenonSettings(row);
    RevealFile(genon.mFileName);
}
