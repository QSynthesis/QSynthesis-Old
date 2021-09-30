#include "../OtoTableTab.h"
#include "Templates/TemporaryMenu.h"

#include <QAction>
#include <QMenu>

void OtoTableTab::openContextMenu() {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
        return;
    }

    QString revealStr;
#if defined(Q_OS_WINDOWS)
    revealStr = tr("Show in Explorer(&S)");
#elif defined(Q_OS_MAC)
    revealStr = tr("Show in Finder(&S)");
#else
    revealStr = tr("Show in File Manager(&S)");
#endif

    QStringList list{tr("Play"),
                     revealStr,
                     "",
                     tr("Move up"),
                     tr("Move down"),
                     tr("Move to top"),
                     tr("Move to bottom"),
                     "",
                     tr("Duplicate"),
                     tr("Remove")};
    TemporaryMenu *menu = new TemporaryMenu(list, this);

    bool isTop = isCurrentTop();
    bool isBottom = isCurrentBottom();
    bool isValid = isCurrentValid();

    if (isTop) {
        menu->setEnabledAt(2, false);
        menu->setEnabledAt(4, false);
    }
    if (isBottom) {
        menu->setEnabledAt(3, false);
        menu->setEnabledAt(5, false);
    }
    if (isTop && isBottom && isValid) {
        menu->setEnabledAt(7, false);
    }
    if (!isValid) {
        menu->setEnabledAt(0, false);
        menu->setEnabledAt(1, false);
    }

    int index = menu->start();
    menu->deleteLater();

    switch (index) {
    case 0:
        playSound(row);
        break;
    case 1:
        reveal();
        break;
    case 2:
        moveUp();
        break;
    case 3:
        moveDown();
        break;
    case 4:
        moveTop();
        break;
    case 5:
        moveBottom();
        break;
    case 6:
        duplicate();
        break;
    case 7:
        remove();
        break;
    default:
        break;
    }
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
