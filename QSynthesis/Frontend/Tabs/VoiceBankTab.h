#ifndef VOICEBANKTAB_H
#define VOICEBANKTAB_H

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QSplitter>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>

#include "CentralTab.h"
#include "QUtauUtils.h"
#include "Utils/FileNameSet.h"
#include "VoiceBank/QVoiceBank.h"
#include "VoiceBankTabs/Areas/OtoDataArea.h"
#include "VoiceBankTabs/Areas/OtoInfoArea.h"
#include "VoiceBankTabs/Areas/OtoVisionArea.h"
#include "VoiceBankTabs/Operations/VoiceOperation.h"

class QOtoReference;
class VoiceActionList;

// Voice Database Tab Class
class VoiceBankTab : public CentralTab {
    Q_OBJECT
public:
    explicit VoiceBankTab(TabWidget *parent = nullptr);
    ~VoiceBankTab();

    VoiceActionList *tabActions;

public:
    bool load() override;
    bool save() override;
    bool restore() override;

    void awake() override;
    void sleep() override;

    void enter() override;
    void leave() override;

    void setFilename(const QString &value) override;
    VoiceBankGroup *ptrs() const;

protected:
    void updateTabName() override;

    void updateMenuRoot() override;
    void updateStatusRoot() override;
    void updateMenuCore() override;

private:
    void loadCore();
    bool saveCore();

    void initTab();
    void initComponents();
    void initValues();

    void initTimer();
    void onOtoTimer();
    void handleBlocks();

private:
    QVoiceBank voicebank;

    FileNameSet otoBlock;
    QTimer *otoTimer;

    // Respond at real time
    void handleCharTxtChanged();
    void handlePrefixMapChanged();
    void handleReadmeTxtChanged();
    void handleOtoFileChanged(QString path);

    void handleOtoDirChanged(QString path);

    // Respond when window is active
    void handleOtoDirChangedCore(QString path);

    // Frontend
private:
    QSplitter *mainSplitter;
    QSplitter *topSplitter;

    QVBoxLayout *mainLayout;

    OtoInfoArea *infoArea;
    OtoDataArea *dataArea;
    OtoVisionArea *visionArea;

    VoiceBankGroup *m_ptrs;

    // To Tuning Tab
private:
    void updateOtoReferences();

    // From Tuning Tab
public:
    bool locateSample(const QGenonSettings &genon);
    void locatePrefix(int noteNum);

    bool exportCurrentSettings(const QString &filename);

    // Main Menu Modify
public:
    void setOffsetByCursor();
    void setConstantByCursor();
    void setBlankByCursor();
    void setPreUttrByCursor();
    void setOverlapByCursor();

    // Main Menu Edit
public:
    void undo() override;
    void redo() override;
    void selectAll() override;
    void deselect() override;

    bool earliest();
    bool latest();

    void addHistory(VoiceOperation *s);
    void clearHistory();

private:
    // Save History for undo and redo
    QVector<VoiceOperation *> historyList;
    int historyIndex;

    int savedHistoryIndex;
};

#endif // VOICEBANKTAB_H
