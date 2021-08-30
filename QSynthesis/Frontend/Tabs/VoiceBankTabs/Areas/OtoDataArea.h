#ifndef OTODATAAREA_H
#define OTODATAAREA_H

#include <QVBoxLayout>
#include <QWidget>

#include "../VoiceTabs/OtoTableTab.h"
#include "TabWidget.h"
#include "VoiceBankArea.h"

class OtoOperation;

class OtoDataArea : public VoiceBankArea {
    Q_OBJECT
public:
    explicit OtoDataArea(VoiceBankTab *tab, QWidget *parent = nullptr);
    ~OtoDataArea();

    void initExtern();

    void saveOperation(OtoOperation *o);                     // Out
    bool handleOperation(OtoOperation *o, bool undo = true); // In

    bool addTable(const QString &dirname, const QOtoSampleList &samples);
    bool removeTable(const QString &dirname);
    bool refreshTable(const QString &dirname);

    bool contains(const QString &dirname) const;
    void removeAll();

    QMap<QString, OtoTableTab *> TableMap;

    OtoTableTab *currentTab();

public:
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

private:
    void init();
};

#endif // OTODATAAREA_H
