#include "../OtoTableTab.h"

void OtoTableTab::setSample(const QOtoSample &sample) {
    table->blockSignals(true);

    int sequence = otoSamples.findAuto(sample);

    QString filename = sample.filename();
    QString base = PathFindFileName(filename);
    int row = findFirstRow(filename);

    while (row < table->rowCount() && fileNameAtRow(row) == base) {
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

    table->blockSignals(false);
}

void OtoTableTab::moveSample(int row, int sequence, int index, int movement) {
    int targetRow = row + movement;
    int targetIndex = index + movement;
    // Swap at backend
    otoSamples[sequence].move(index, targetIndex);

    // Swap at frontend
    table->blockSignals(true);
    moveRow(row, targetRow);
    selectNone();
    selectRow(targetRow);
    sendCurrentToVision(targetRow, sequence, targetIndex);
    table->blockSignals(false);
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
    table->blockSignals(true);
    setGenonSettings(targetRow, genon);
    selectNone();
    selectRow(targetRow);
    sendCurrentToVision(targetRow, sequence, index);
    table->blockSignals(false);

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
    } else {
        // Change backend value
        QOtoSample &sample = otoSamples[sequence];
        sample.insert(index, genon);
        targetRow += index;
    }

    // Change frontend value
    table->blockSignals(true);
    insertRow(targetRow, genon);
    selectNone();
    selectRow(targetRow);
    sendCurrentToVision(targetRow, sequence, index);
    table->blockSignals(false);
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
        otoSamples.removeAt(sequence);
    } else {
        otoSamples[sequence].removeAt(index);
    }
    targetRow += index;

    // Change frontend value
    table->blockSignals(true);
    removeRow(targetRow);
    selectNone();
    sendNoneToVision();
    table->blockSignals(false);
}

bool OtoTableTab::selectSample(const QGenonSettings &genon) {
    QString filename = genon.mFileName;
    int sequence = otoSamples.findAuto(filename);

    table->setFocus();

    if (sequence >= 0) {
        const QOtoSample &sample = otoSamples.at(sequence);
        int index = sample.indexOf(genon);
        if (index >= 0) {
            int row = findFirstRow(filename);
            row += index;
            if (row < table->rowCount()) {
                selectNone();
                selectRow(row);
                return true;
            }
        }
    }

    return false;
}
