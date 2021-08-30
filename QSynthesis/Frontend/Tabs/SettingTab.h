#ifndef SETTINGTAB_H
#define SETTINGTAB_H

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QRadioButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

#include "CentralTab.h"
#include "Customs/LinearScrollArea.h"
#include "QUtils.h"
#include "SettingTabs/Operations/SettingOperation.h"

class SettingActionList;

// Setting Tab Class
class SettingTab : public CentralTab {
    Q_OBJECT
public:
    explicit SettingTab(TabWidget *parent = nullptr);
    ~SettingTab();

    SettingActionList *tabActions;

public:
    static bool getDefaultSettings(const QString &filename);

    bool load() override;
    bool save() override;
    bool restore() override;

    void awake() override;
    void sleep() override;

    void setFixedname(const QString &value) override;

protected:
    void updateMenuRoot() override;
    void updateMenuCore() override;

private:
    QHBoxLayout *mainLayout;

    QLabel *title;
    QToolButton *toEdit;
    QToolButton *toKeyboard;
    QToolButton *toMouse;
    QToolButton *toRender;
    QToolButton *toCache;

    LinearScrollArea *mainScroll;
    QWidget *settingContent;
    QVBoxLayout *contentLayout;

    // 1 Edit
    QLabel *edit;
    QCheckBox *propertyClear;
    QCheckBox *batchMove;

    // 2 Keyboard
    QLabel *keyboard;
    // 2.1 Wheel
    QGroupBox *wheel;
    QComboBox *HZoom;
    QComboBox *VZoom;
    QComboBox *HMove;
    QComboBox *VMove;
    // 2.2 Drag
    QGroupBox *drag;
    QComboBox *pageDrag;
    QComboBox *regionSelect;
    QComboBox *addPointForward;
    // 2.3 Mode2
    QGroupBox *mode2;
    QComboBox *mode2_HAttach;
    QComboBox *mode2_VAttach;
    QComboBox *mode2_CAttach;
    // 2.4 Envelope
    QGroupBox *envelope;
    QComboBox *envelope_HAttach;
    QComboBox *envelope_VAttach;
    QComboBox *envelope_CAttach;
    // 2.5 Right Click
    QGroupBox *rightClick;
    QComboBox *defaultMenu;
    QComboBox *pluginMenu;
    QComboBox *sampleMenu;
    QComboBox *toolMenu;
    QComboBox *immRender;
    // 2.6 Drag Backward
    QGroupBox *backward;
    QComboBox *moveNoteBackward;
    QComboBox *singleCoverBackward;
    QComboBox *anyCoverBackward;
    // 2.7 Drag Forward
    QGroupBox *forward;
    QComboBox *moveNoteForward;
    QComboBox *stretchNoteForward;
    QComboBox *addRestForward;

    // 3 Mouse
    QLabel *mouse;
    // 3.1 Mode2-Add
    QGroupBox *mode2_Add;
    QComboBox *mode2_AddPoint;
    // 3.2 Mode2-Modify
    QGroupBox *mode2_Modify;
    QComboBox *mode2_RemovePoint;
    QComboBox *mode2_ChangeType;
    QComboBox *mode2_OpenMenu;
    // 3.3 Envelope-Add
    QGroupBox *envelope_Add;
    QComboBox *envelope_AddPoint;
    // 3.4 Envelope-Modify
    QGroupBox *envelope_Modify;
    QComboBox *envelope_RemovePoint;
    QComboBox *envelope_Standardize;
    QComboBox *envelope_OpenMenu;

    // 4 Render
    QLabel *render;
    QCheckBox *notBase64;
    QCheckBox *notCMD;
    QComboBox *threadNum;

    // 5 Cache
    QLabel *cache;
    QCheckBox *noCache;
    // 5.1 Clear
    QGroupBox *cacheClear;
    QRadioButton *noClear;
    QRadioButton *clearOnFileClose;
    QRadioButton *clearOnWindowClose;
    QRadioButton *clearWhenFull;
    QSpinBox *cacheCapacity;

    void navigateConnectManager();
    void editConnectManager();
    void setEditState(const SettingType type, const QString &key, const QJsonValue &val);

    QHBoxLayout *HLayout(const QList<QWidget *> &list, const QFont &font, int sapce = 0);
    QVBoxLayout *NavigateLayout(const QList<QToolButton *> &list, const QFont &font,
                                const QString &itemStyle = "");
    QGroupBox *ComboGroup(const QString &name, const QList<QWidget *> &wlist,
                          const QList<QComboBox *> &clist, const QFont &font);
    void comboGroupManager(const QList<QComboBox *> &clist, const QStringList &slist,
                           const QString &defaultText = "");

    bool parseFile(const QString &filename);

signals:
    void settingsChanged();

public:
    void undo() override;
    void redo() override;

    bool earliest();
    bool latest();

    // Methods for Notes Area
    void addHistory(SettingOperation *s);
    void clearHistory();

private:
    QJsonObject settingObj;

    // Save History for undo and redo
    SettingOperation *opQueue;
    QVector<SettingOperation *> historyList;
    int historyIndex;
    int savedHistoryIndex;

    bool historyBlock;
    bool historyLink;

    bool operationHandler(SettingOperation *op, bool undo = false);
};

#endif // SETTINGTAB_H
