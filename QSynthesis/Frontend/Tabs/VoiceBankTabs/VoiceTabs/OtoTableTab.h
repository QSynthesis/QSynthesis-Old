#ifndef OTOTABLETAB_H
#define OTOTABLETAB_H

#include <QHeaderView>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "../../BaseTab.h"
#include "QOtoSampleList.h"

class QHeaderView;

class OtoTableTab : public BaseTab {
    Q_OBJECT
    Q_PROPERTY(QColor normalColor READ normalColor WRITE setNormalColor NOTIFY colorChanged)
    Q_PROPERTY(QColor emptyColor READ emptyColor WRITE setEmptyColor NOTIFY colorChanged)

public:
    explicit OtoTableTab(TabWidget *parent = nullptr);
    ~OtoTableTab();

    QString dirname() const;
    void setDirname(const QString &dirname);

    // From initialization
    void setOtoSamples(const QOtoSampleList &otoSamples);
    QOtoSampleList OtoSamples() const;

    // From undo and redo
    void setSample(const QOtoSample &sample);
    void moveSample(int row, int sequence, int index, int movement);
    void moveSample(const QGenonSettings &genon, int index, int movement);
    void changeSample(const QGenonSettings &genon, int index);
    void addSample(const QGenonSettings &genon, int index = 0);
    void removeSample(const QGenonSettings &genon, int index = 0);

    // From tuning tab
    bool selectSample(const QGenonSettings &genon);

    // From vision
    void setCurrentSample(const QGenonSettings &genon);

    // From update
    void refresh();

public:
    QColor normalColor() const;
    void setNormalColor(const QColor &normalColor);

    QColor emptyColor() const;
    void setEmptyColor(const QColor &emptyColor);

    QColor invalidColor() const;
    void setInvalidColor(const QColor &invalidColor);

private:
    void addRow(const QGenonSettings &genon);
    void insertRow(int row, const QGenonSettings &genon);
    void insertRow(int row, const QStringList &list);
    void removeRow(int row);

    void selectNone();
    void selectRow(int row);

    void swapRow(int row1, int row2);
    void moveRow(int from, int to);

    int findFirstRow(const QString &filename) const;

    QGenonSettings getGenonSettings(int row) const;
    void setGenonSettings(int row, const QGenonSettings &genon);

    void updateRowStatus(int row);

    void turnLineToEmpty(int row);
    void turnLineToInvalid(int row);
    void turnLineToNormal(int row);

    void playSound(int row) const;

    void openContextMenu();

    void handlePlayTriggered();
    void handleMoveUpTriggered();
    void handleMoveDownTriggered();
    void handleMoveTopTriggered();
    void handleMoveBottomTriggered();
    void handleDuplicateTriggered();
    void handleRemoveTriggered();
    void handleRevealTriggered();

private:
    QMenu *m_menu;

    QVBoxLayout *mainLayout;
    QTableWidget *otoTable;
    QOtoSampleList otoSamples;

    QString m_dirname;

    QColor m_normalColor;
    QColor m_emptyColor;
    QColor m_invalidColor;

    int currentRow;      // Row at table
    int currentSequence; // Index at samples list
    int currentIndex;    // Index at sample

    QMap<QString, QPair<bool, bool>> validCache;

    void init();

    QString fileNameAtRow(int row) const;

    // To Vision
    void sendCurrentToVision(int row, int sequence, int index);
    void sendCurrentToVision(const QGenonSettings &sample, int index);
    void sendNoneToVision();

    void handleCellChanged(int row, int column);
    void handleCurrentChanged(int currentRow, int currentColumn, int previousRow,
                              int previousColumn);
    void handleCellDoubleClicked(int row, int column);

private:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void colorChanged();

    void sampleChanged(const QGenonSettings &origin, const QGenonSettings &modified, int index);
    void sampleMoved(const QGenonSettings &sample, int index, int movement);
    void sampleAdded(const QGenonSettings &sample, int index);
    void sampleRemoved(const QGenonSettings &sample, int index);

    void currentChanged(const QGenonSettings &genon, int index);
};

#endif // OTOTABLETAB_H
