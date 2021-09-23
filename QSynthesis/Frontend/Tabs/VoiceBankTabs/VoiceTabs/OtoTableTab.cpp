#include "OtoTableTab.h"

#include <QAction>
#include <QMenu>

OtoTableTab::OtoTableTab(TabWidget *parent) : BaseTab(parent) {
    init();
}

OtoTableTab::~OtoTableTab() {
}

void OtoTableTab::init() {
    currentRow = -1;
    currentSequence = -1;
    currentIndex = -1;

    m_normalColor = QColor(255, 255, 255, 0);
    m_emptyColor = QColor(0, 255, 0, 32);
    m_invalidColor = QColor(255, 0, 0, 32);

    table = new QTableWidget(this);
    table->viewport()->installEventFilter(this);

    table->setProperty("type", "voice");
    mainLayout = new QVBoxLayout(this);

    table->setColumnCount(8);
    QStringList header{tr("File Name"), tr("Alias"),        tr("Offset"),  tr("Consonant"),
                       tr("Blank"),     tr("PreUtterance"), tr("Overlap"), tr("Frq")};

    table->setHorizontalHeaderLabels(header);
    table->horizontalHeader()->setDisabled(false);
    table->horizontalHeader()->setHighlightSections(false);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table->setAlternatingRowColors(true);

    mainLayout->addWidget(table);
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(table, &QTableWidget::cellChanged, this, &OtoTableTab::handleCellChanged);
    connect(table, &QTableWidget::cellDoubleClicked, this, &OtoTableTab::handleCellDoubleClicked);
    connect(table, &QTableWidget::itemSelectionChanged, this, &OtoTableTab::handleSelectionChanged);
}

int OtoTableTab::findFirstRow(const QString &filename) const {
    QString key = PathFindFileName(filename);
    // Binary Search
    int i, j, mid;
    i = 0;
    j = table->rowCount() - 1;
    while (i <= j) {
        mid = i + (j - i) / 2;
        if (fileNameAtRow(mid).toLower() < key.toLower()) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }
    return i;
}

QGenonSettings OtoTableTab::getGenonSettings(int row) const {
    QGenonSettings genon;

    genon.mFileName = m_dirname + Slash + fileNameAtRow(row);
    genon.mAlias = table->item(row, 1)->text();
    genon.mOffset = table->item(row, 2)->text().toDouble();
    genon.mConstant = table->item(row, 3)->text().toDouble();
    genon.mBlank = table->item(row, 4)->text().toDouble();
    genon.mPreUtterance = table->item(row, 5)->text().toDouble();
    genon.mVoiceOverlap = table->item(row, 6)->text().toDouble();

    return genon;
}

void OtoTableTab::setGenonSettings(int row, const QGenonSettings &genon) {
    table->item(row, 0)->setText(PathFindFileName(genon.mFileName));
    table->item(row, 1)->setText(genon.mAlias);
    table->item(row, 2)->setText(QString::number(genon.mOffset));
    table->item(row, 3)->setText(QString::number(genon.mConstant));
    table->item(row, 4)->setText(QString::number(genon.mBlank));
    table->item(row, 5)->setText(QString::number(genon.mPreUtterance));
    table->item(row, 6)->setText(QString::number(genon.mVoiceOverlap));
    table->item(row, 7)->setText(genon.frqExist() ? "TRUE" : "FALSE");
}

void OtoTableTab::updateRowStatus(int row) {
    table->blockSignals(true);
    QGenonSettings genon = getGenonSettings(row);
    if (!genon.valid()) {
        turnLineToInvalid(row);
    } else if (genon.isEmpty()) {
        turnLineToEmpty(row);
    } else {
        turnLineToNormal(row);
    }
    table->item(row, 7)->setText(genon.frqExist() ? "TRUE" : "FALSE");
    table->blockSignals(false);
}

void OtoTableTab::turnLineToEmpty(int row) {
    // qDebug() << "Line " << row << ": to be green";
    for (int column = 0; column < 8; ++column) {
        table->item(row, column)->setBackground(m_emptyColor);
    }
}

void OtoTableTab::turnLineToInvalid(int row) {
    // qDebug() << "Line " << row << ": to be red";
    for (int column = 0; column < 8; ++column) {
        table->item(row, column)->setBackground(m_invalidColor);
    }
}

void OtoTableTab::turnLineToNormal(int row) {
    // qDebug() << "Line " << row << ": to be white";
    for (int column = 0; column < 8; ++column) {
        table->item(row, column)->setBackground(m_normalColor);
    }
}

QString OtoTableTab::fileNameAtRow(int row) const {
    return table->item(row, 0)->text();
}

void OtoTableTab::sendCurrentToVision(int row, int sequence, int index) {
    QGenonSettings sample = getGenonSettings(row);
    currentRow = row;
    currentSequence = sequence;
    currentIndex = index;

    emit currentChanged(sample, currentIndex);
}

void OtoTableTab::sendCurrentToVision(const QGenonSettings &sample, int index) {
    currentRow = findFirstRow(sample.mFileName);
    currentSequence = otoSamples.findAuto(sample.mFileName);
    currentIndex = index;

    emit currentChanged(sample, currentIndex);
}

void OtoTableTab::sendNoneToVision() {
    emit currentChanged(QGenonSettings(), -1);
}

void OtoTableTab::handleCellChanged(int row, int column) {
    QGenonSettings genon = getGenonSettings(row);

    int firstRow = findFirstRow(genon.mFileName);
    //    while (firstRow - 1 >= 0 && fileNameAtRow(firstRow - 1) == fileNameAtRow(row)) {
    //        firstRow--;
    //    }

    int index = row - firstRow;

    int sequence = otoSamples.findAuto(genon.mFileName);
    if (sequence < 0) {
        return;
    }
    QOtoSample &sample = otoSamples[sequence];
    QGenonSettings &originGenon = sample[index];

    // Numerical judge
    if (column >= 2 && column <= 6) {
        QString text = table->item(row, column)->text();
        double value;
        bool isNum;

        value = text.toDouble(&isNum);
        if (!isNum) {
            qDebug() << "[Oto Change] Not a number";
            // Change back
            table->blockSignals(true);
            switch (column) {
            case 2:
                table->item(row, column)->setText(QString::number(originGenon.mOffset));
                break;
            case 3:
                table->item(row, column)->setText(QString::number(originGenon.mConstant));
                break;
            case 4:
                table->item(row, column)->setText(QString::number(originGenon.mBlank));
                break;
            case 5:
                table->item(row, column)->setText(QString::number(originGenon.mPreUtterance));
                break;
            case 6:
                table->item(row, column)->setText(QString::number(originGenon.mVoiceOverlap));
                break;
            default:
                break;
            }
            table->blockSignals(false);
            return;
        }
    }

    // Change backend value
    QGenonSettings origin = sample[index];
    sample[index] = genon;

    updateRowStatus(row);
    sendCurrentToVision(row, sequence, index);
    emit sampleChanged(origin, genon, index);
}

void OtoTableTab::handleCellDoubleClicked(int row, int column) {
    if (column == 0) {
        playSound(row);
    }
}

void OtoTableTab::handleSelectionChanged() {
    int currentRow = selectedRow();
    if (currentRow < 0 || currentRow >= table->rowCount()) {
        sendNoneToVision();
    } else {
        QGenonSettings genon = getGenonSettings(currentRow);
        int sequence = otoSamples.findAuto(genon.mFileName);
        int firstRow = findFirstRow(genon.mFileName);
        int index = currentRow - firstRow;

        sendCurrentToVision(currentRow, sequence, index);
    }
    emit selectionChanged();
}

bool OtoTableTab::eventFilter(QObject *obj, QEvent *event) {
    if (obj == table->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            int row = table->rowAt(mouseEvent->pos().y());
            if (row >= 0 && row < table->rowCount()) {
                selectNone();
                selectRow(row);
                openContextMenu();
                return true;
            }
        }
    }
    return BaseTab::eventFilter(obj, event);
}

void OtoTableTab::setOtoSamples(const QOtoSampleList &otoSamples) {
    this->otoSamples = otoSamples;

    table->blockSignals(true);
    for (auto it = otoSamples.begin(); it != otoSamples.end(); ++it) {
        const QOtoSample &sample = *it;
        for (int i = 0; i < sample.size(); ++i) {
            QGenonSettings genon = sample.at(i);
            addRow(genon);
        }
        validCache.insert(sample.filename(), qMakePair(sample.valid(), sample.frqExist()));
    }
    table->blockSignals(false);
}

void OtoTableTab::setCurrentSample(const QGenonSettings &genon) {
    if (currentRow < 0 || currentRow >= table->rowCount()) {
        return;
    }
    if (currentSequence < 0 || currentSequence >= otoSamples.size()) {
        return;
    }
    QOtoSample &sample = otoSamples[currentSequence];
    if (currentIndex < 0 || currentIndex >= sample.size()) {
        return;
    }
    // Reload backend
    sample[currentIndex] = genon;

    // Reload frontend
    table->blockSignals(true);
    setGenonSettings(currentRow, genon);
    table->selectRow(currentRow);
    table->blockSignals(false);

    updateRowStatus(currentRow);
}

void OtoTableTab::refresh() {
    QDir dir(m_dirname);
    QFileInfoList waveInfos =
        dir.entryInfoList({"*.wav"}, QDir::NoDotAndDotDot | QDir::Files, QDir::Time);

    for (auto it = validCache.begin(); it != validCache.end(); ++it) {
        QGenonSettings genon(it.key());
        bool toRefresh = false;
        // Update Cache
        if ((genon.valid() != it.value().first)) {
            toRefresh = true;
            it.value().first = genon.valid();
        }
        if ((genon.frqExist() != it.value().second)) {
            toRefresh = true;
            it.value().second = genon.frqExist();
        }
        // Refresh
        if (toRefresh) {
            int firstRow = findFirstRow(genon.mFileName);
            int row = firstRow;
            while (row < table->rowCount() && fileNameAtRow(row) == fileNameAtRow(firstRow)) {
                updateRowStatus(row);
                row++;
            }
        }
    }
    table->blockSignals(true);
    for (QFileInfo &info : waveInfos) {
        QString path = info.absoluteFilePath();
        int targetPosition = 0;
        int index = otoSamples.findAuto(path, &targetPosition);
        if (index < 0) {
            QGenonSettings genon;
            genon.mFileName = path;
            QOtoSample sample(path);
            sample.append(genon);
            otoSamples.insert(targetPosition, sample);

            int row = findFirstRow(genon.mFileName);
            insertRow(row, genon);
        }
    }
    table->blockSignals(false);
    selectNone();
    sendNoneToVision();
}

int OtoTableTab::selectedRow() const {
    if (table->selectedRanges().isEmpty()) {
        return -1;
    }
    return table->currentRow();
}

bool OtoTableTab::isSelectionSingle() const {
    const QList<QTableWidgetSelectionRange> &ranges = table->selectedRanges();
    if (ranges.size() == 1) {
        const QTableWidgetSelectionRange &range = ranges.front();
        if (range.topRow() == range.bottomRow()) {
            return true;
        }
    }
    return false;
}

bool OtoTableTab::isCurrentTop() const {
    bool isTop = false;

    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
        return true;
    }

    if (row == 0 || fileNameAtRow(row) != fileNameAtRow(row - 1)) {
        isTop = true;
    }
    return isTop;
}

bool OtoTableTab::isCurrentBottom() const {
    bool isBottom = false;

    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
        return true;
    }

    if (row == table->rowCount() - 1 || fileNameAtRow(row) != fileNameAtRow(row + 1)) {
        isBottom = true;
    }
    return isBottom;
}

bool OtoTableTab::isCurrentValid() const {
    int row = selectedRow();
    if (row < 0 || row >= table->rowCount()) {
        return false;
    }
    return getGenonSettings(row).valid();
}
