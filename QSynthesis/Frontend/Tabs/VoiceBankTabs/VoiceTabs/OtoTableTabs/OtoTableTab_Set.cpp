#include "../OtoTableTab.h"

void OtoTableTab::setSample(const QOtoSample &sample) {
    otoTable->blockSignals(true);

    int sequence = otoSamples.findAuto(sample);

    QString filename = sample.filename();
    QString base = PathFindFileName(filename);
    int row = findFirstRow(filename);

    while (row < otoTable->rowCount() && fileNameAtRow(row) == base) {
        removeRow(row);
    }

    if (sample.isEmpty()) {
        if (sequence >= 0) {
            otoSamples.removeAt(sequence);
        }
    } else {
        otoSamples.insertAuto(sample, true);
        for (int i = 0; i < sample.size(); ++i) {
            QGenonSettings genon = sample.at(i);
            insertRow(row, genon);
            row++;
        }
    }

    otoTable->blockSignals(false);
}

void OtoTableTab::moveSample(int row, int sequence, int index, int movement) {
    int targetRow = row + movement;
    int targetIndex = index + movement;
    // Swap at backend
    otoSamples[sequence].move(index, targetIndex);

    // Swap at frontend
    otoTable->blockSignals(true);
    moveRow(row, targetRow);
    selectRow(targetRow);
    sendCurrentToVision(targetRow, sequence, targetIndex);
    otoTable->blockSignals(false);
}

void OtoTableTab::moveSample(const QGenonSettings &genon, int index, int movement) {
    int sequence = otoSamples.findAuto(genon.mFileName);
    int row = findFirstRow(genon.mFileName);
    moveSample(row + index, sequence, index, movement);
}

void OtoTableTab::changeSample(const QGenonSettings &genon, int index) {
    QString filename = genon.mFileName;

    int row = findFirstRow(filename);
    int targetIndex = 0;
    int sequence = otoSamples.findAuto(filename, &targetIndex);

    if (sequence < 0) {
        return;
    }

    // Change backend value
    otoSamples[sequence][index] = genon;

    int targetRow = row + index;
    // Change frontend value
    otoTable->blockSignals(true);
    setGenonSettings(targetRow, genon);
    selectRow(targetRow);
    sendCurrentToVision(targetRow, sequence, index);
    otoTable->blockSignals(false);

    updateRowStatus(targetRow);
}

void OtoTableTab::addSample(const QGenonSettings &genon, int index) {
    QString filename = genon.mFileName;

    int row = findFirstRow(filename);
    int targetIndex = 0;
    int targetRow = row;
    int sequence = otoSamples.findAuto(filename, &targetIndex);

    if (sequence < 0) {
        // Add to backend
        QOtoSample sample(filename);
        sample.append(genon);
        otoSamples.insert(targetIndex, sample);
        validCache.insert(sample.filename(), qMakePair(sample.valid(), sample.frqExist()));
    } else {
        // Change backend value
        QOtoSample &sample = otoSamples[sequence];
        sample.insert(index, genon);
        targetRow += index;
    }

    // Change frontend value
    otoTable->blockSignals(true);
    insertRow(targetRow, genon);
    selectRow(targetRow);
    sendCurrentToVision(targetRow, sequence, index);
    otoTable->blockSignals(false);
}

void OtoTableTab::removeSample(const QGenonSettings &genon, int index) {
    QString filename = genon.mFileName;

    int row = findFirstRow(filename);
    int targetIndex = 0;
    int targetRow = row;
    int sequence = otoSamples.findAuto(filename, &targetIndex);

    if (sequence < 0) {
        return;
    }
    // Change backend value
    if (otoSamples[sequence].size() == 1) {
        validCache.remove(otoSamples[sequence].filename());
        otoSamples.removeAt(sequence);
    } else {
        otoSamples[sequence].removeAt(index);
    }
    targetRow += index;

    // Change frontend value
    otoTable->blockSignals(true);
    removeRow(targetRow);
    selectNone();
    sendNoneToVision();
    otoTable->blockSignals(false);
}

bool OtoTableTab::selectSample(const QGenonSettings &genon) {
    QString filename = genon.mFileName;
    int sequence = otoSamples.findAuto(filename);

    if (sequence >= 0) {
        const QOtoSample &sample = otoSamples.at(sequence);
        int index = sample.indexOf(genon);
        qDebug() << index;
        if (index >= 0) {
            int row = findFirstRow(filename);
            row += index;
            if (row < otoTable->rowCount()) {
                selectRow(row);
                return true;
            }
        }
    }

    return false;
}
