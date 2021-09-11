#ifndef TRACKSINTERFACE_H
#define TRACKSINTERFACE_H

#include <QGridLayout>
#include <QMenu>

#include "../Areas/Tracks/BlocksArea.h"
#include "../Areas/Tracks/HeadsArea.h"
#include "../Modules/Elements/SectionsLine.h"
#include "../Modules/Scrolls/NoneScrollArea.h"
#include "BaseInterface.h"
#include "QUtils.h"
#include "Templates/VectorButton.h"
#include "Utils/ItemList.h"

class TracksForm;
class TuningGroup;
class GraphicsNote;

class TracksInterface : public BaseInterface {
    Q_OBJECT
public:
    explicit TracksInterface(TracksForm *parent = nullptr);
    virtual ~TracksInterface();

    void initDefaultTrack();
    void adjustDefaultTrack();

    void setDefaultResampler(const QString &resampler);
    void setDefaultFlags(const QString &flags);
    void setDefaultName(const QString &name);
    void setDefaultVoice(const QString &voice);

    QString defaultResampler() const;
    QString defaultName() const;
    QString defaultFlags() const;
    QString defaultVoiceDir() const;

public:
    void setVisionStatus(Qs::Panels::Tracks mode);

    TuningGroup *ptrs() const;

private:
    TuningGroup *m_ptrs;

    HeadsArea *lefts;
    BlocksArea *rights;

    NoneScrollArea *sectionsScroll;
    SectionsLine *sections;

    NoneScrollArea *leftScroll;
    QScrollArea *rightScroll;

    QGridLayout *mainLayout;
    QHBoxLayout *topLeftLayout;

    VectorButton *btnMenu;

    QMenu *m_menu;

    void handleHorizontalMove(int value);
    void handleVerticalMove(int value);

    void handleVoiceChanged(int index, QString newVal);
    void handleResamplerChanged(int index, QString newVal);
    void handleNameChanged(int index, QString newVal);
    void handleFlagsChanged(int index, QString newVal);

    void handleMenuBtnClicked();
    void handleConfigTriggered();
    void handleCharsetTriggered();
};

#endif // TRACKSINTERFACE_H
