#ifndef OTODATAAREA_H
#define OTODATAAREA_H

#include <QVBoxLayout>
#include <QWidget>

#include "../VoiceTabs/OtoTableTab.h"
#include "TabWidget.h"
#include "VoiceBankArea.h"

class OtoOperation;
class QOtoIni;

class OtoDataArea : public VoiceBankArea {
    Q_OBJECT
public:
    explicit OtoDataArea(VoiceBankTab *tab, QWidget *parent = nullptr);
    ~OtoDataArea();

    void initExtern();

public:
    void saveOperation(OtoOperation *o);                     // Out
    bool handleOperation(OtoOperation *o, bool undo = true); // In

    void loadTables(const QList<QOtoIni> &data);
    QList<QOtoIni> exportTables() const;

    bool notifyTable(const QStringList &files);
    bool contains(const QString &dirname) const;

private:
    bool addTable(const QString &dirname, const QOtoSampleList &samples);
    bool removeTable(const QString &dirname);
    void removeAllTables();

    void complementSamples(const QString &dirname, QOtoSampleList &samples);

public:
    QMap<QString, OtoTableTab *> TableMap;
    OtoTableTab *currentTab();

    bool locateSample(const QGenonSettings &genon);
    void receiveFromVision(const QGenonSettings &sample); // Oto Handle

private:
    QVBoxLayout *mainLayout;
    TabWidget *otoTabs;

    void handleSampleChanged(const QGenonSettings &origin, const QGenonSettings &modified,
                             int index);
    void handleSampleMoved(const QGenonSettings &sample, int index, int movement);
    void handleSampleAdded(const QGenonSettings &sample, int index);
    void handleSampleRemoved(const QGenonSettings &sample, int index);
    void handleCurrentChanged(const QGenonSettings &genon, int index);

    void handleSelectionChanged();
    void handleTabIndexChanged(int index);

private:
    void init();
};

#endif // OTODATAAREA_H
