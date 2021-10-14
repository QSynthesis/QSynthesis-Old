#include "SettingTab.h"
#include "mainwindow.h"

SettingTab::SettingTab(CentralTabWidget *parent) : CentralTab(parent) {
    m_type = Qs::Setting;

    // unified style
    QFont titleFont = mainFont(30, QFont::Bold);
    QFont textFont = mainFont(20);
    QString titleStyle = "padding-left: 10px; padding-top: 15px; padding-bottom: 15px;";
    QString indent = "padding-left: 60px; padding-right: 120px;";
    QString comboDefault = tr("(Undefined)");
    int gap = 40, padding = 60;

    // temp variables
    QStringList slist;
    QList<QWidget *> wlist, wlist2;
    QList<QComboBox *> clist;
    QList<QToolButton *> tlist;
    QWidget *tmpWidget;
    QVBoxLayout *tmpVLayout;


    // main container
    mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    // add title and navigation
    tmpVLayout = new QVBoxLayout();

    title = new QLabel(tr("Settings"));
    title->setFont(mainFont(50, QFont::Bold));
    title->setAlignment(Qt::AlignTop | Qt::AlignRight);
    title->setStyleSheet("padding-top: 40px; padding-bottom: 20px;\
                          padding-left: 60px; padding-right: 60px;");
    tmpVLayout->addWidget(title);
    tmpVLayout->setAlignment(title, Qt::AlignTop | Qt::AlignRight);

    toEdit = new QToolButton();
    toEdit->setText(tr("Edit \u2022"));
    toKeyboard = new QToolButton();
    toKeyboard->setText(tr("KeyBoard Modifier \u2022"));
    toMouse = new QToolButton();
    toMouse->setText(tr("Mouse Click Modifier \u2022"));
    toRender = new QToolButton();
    toRender->setText(tr("Render \u2022"));
    toCache = new QToolButton();
    toCache->setText(tr("Cache \u2022"));

    tlist.clear();
    tlist.append(toEdit);
    tlist.append(toKeyboard);
    tlist.append(toMouse);
    tlist.append(toRender);
    tlist.append(toCache);
    tmpVLayout->addLayout(
        NavigateLayout(tlist, textFont, "padding-left: 10px; padding-right: 10px;"));

    tmpWidget = new QWidget();
    tmpWidget->setLayout(tmpVLayout);
    tmpWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    mainLayout->addWidget(tmpWidget);

    // add scroll area
    mainScroll = new LinearScrollArea(Qt::Vertical);
    mainScroll->setFrameStyle(QFrame::NoFrame);
    mainLayout->addWidget(mainScroll);

    // content layout
    contentLayout = new QVBoxLayout();
    contentLayout->setMargin(0);

    // 1 Edit
    edit = new QLabel(tr("Edit"));
    edit->setFont(titleFont);
    edit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    edit->setStyleSheet(titleStyle);
    contentLayout->addWidget(edit);

    propertyClear = new QCheckBox(tr("Clear other properties on Words Changed"));
    propertyClear->setFont(textFont);
    propertyClear->setStyleSheet(indent);
    contentLayout->addWidget(propertyClear);

    batchMove = new QCheckBox(tr("Notes batch move"));
    batchMove->setFont(textFont);
    batchMove->setStyleSheet(indent);
    contentLayout->addWidget(batchMove);

    contentLayout->addSpacing(gap);

    // 2 Keyboard
    keyboard = new QLabel(tr("Keyboard Modifier"));
    keyboard->setFont(titleFont);
    keyboard->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    keyboard->setStyleSheet(titleStyle);
    contentLayout->addWidget(keyboard);

    slist.clear();
    slist.append(tr("None"));
    slist.append("Ctrl");
    slist.append("Shift");
    slist.append("Alt");
    slist.append("Ctrl+Shift");
    slist.append("Ctrl+Alt");
    slist.append("Shift+Alt");
    slist.append("Ctrl+Shift+Alt");
    slist.append(comboDefault);

    // 2.1 Wheel
    wlist.clear();
    clist.clear();
    HZoom = new QComboBox();
    wlist.append(new QLabel(tr("Horizontal Zoom ")));
    clist.append(HZoom);
    VZoom = new QComboBox();
    wlist.append(new QLabel(tr("Vertical Zoom ")));
    clist.append(VZoom);
    HMove = new QComboBox();
    wlist.append(new QLabel(tr("Horizontal Move ")));
    clist.append(HMove);
    VMove = new QComboBox();
    wlist.append(new QLabel(tr("Vertical Move ")));
    clist.append(VMove);
    wheel = ComboGroup(tr("Wheel"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(wheel);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(HZoom);
    clist.append(VZoom);
    clist.append(HMove);
    clist.append(VMove);
    comboGroupManager(clist, slist, comboDefault);

    // 2.2 Drag
    wlist.clear();
    clist.clear();
    pageDrag = new QComboBox();
    wlist.append(new QLabel(tr("Page Drag ")));
    clist.append(pageDrag);
    regionSelect = new QComboBox();
    wlist.append(new QLabel(tr("Region Select when drawing ")));
    clist.append(regionSelect);
    addPointForward = new QComboBox();
    wlist.append(new QLabel(tr("Add Point at note forward in Mode2 ")));
    clist.append(addPointForward);
    drag = ComboGroup(tr("Drag"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(drag);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(pageDrag);
    clist.append(regionSelect);
    clist.append(addPointForward);
    comboGroupManager(clist, slist, comboDefault);

    // 2.3 Mode2
    wlist.clear();
    clist.clear();
    mode2_HAttach = new QComboBox();
    wlist.append(new QLabel(tr("Point horizontal attach ")));
    clist.append(mode2_HAttach);
    mode2_VAttach = new QComboBox();
    wlist.append(new QLabel(tr("Point vertical attach ")));
    clist.append(mode2_VAttach);
    mode2_CAttach = new QComboBox();
    wlist.append(new QLabel(tr("Point align to semitone ")));
    clist.append(mode2_CAttach);
    mode2 = ComboGroup(tr("Mode2"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(mode2);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(mode2_HAttach);
    clist.append(mode2_VAttach);
    clist.append(mode2_CAttach);
    comboGroupManager(clist, slist, comboDefault);

    // 2.4 Envelope
    wlist.clear();
    clist.clear();
    envelope_HAttach = new QComboBox();
    wlist.append(new QLabel(tr("Point horizontal attach ")));
    clist.append(envelope_HAttach);
    envelope_VAttach = new QComboBox();
    wlist.append(new QLabel(tr("Point vertical attach ")));
    clist.append(envelope_VAttach);
    envelope_CAttach = new QComboBox();
    wlist.append(new QLabel(tr("Point align to half volume ")));
    clist.append(envelope_CAttach);
    envelope = ComboGroup(tr("Envelope"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(envelope);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(envelope_HAttach);
    clist.append(envelope_VAttach);
    clist.append(envelope_CAttach);
    comboGroupManager(clist, slist, comboDefault);

    // 2.5 Right Click
    wlist.clear();
    clist.clear();
    defaultMenu = new QComboBox();
    wlist.append(new QLabel(tr("Open default menu ")));
    clist.append(defaultMenu);
    pluginMenu = new QComboBox();
    wlist.append(new QLabel(tr("Open plugin menu ")));
    clist.append(pluginMenu);
    sampleMenu = new QComboBox();
    wlist.append(new QLabel(tr("Open similar sample menu ")));
    clist.append(sampleMenu);
    toolMenu = new QComboBox();
    wlist.append(new QLabel(tr("Open tool menu ")));
    clist.append(toolMenu);
    immRender = new QComboBox();
    wlist.append(new QLabel(tr("Render immediately ")));
    clist.append(immRender);
    rightClick = ComboGroup(tr("Right Click"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(rightClick);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(defaultMenu);
    clist.append(pluginMenu);
    clist.append(sampleMenu);
    clist.append(toolMenu);
    clist.append(immRender);
    comboGroupManager(clist, slist, comboDefault);

    // 2.6 Drag Backward
    wlist.clear();
    clist.clear();
    moveNoteBackward = new QComboBox();
    wlist.append(new QLabel(tr("Move notes followed ")));
    clist.append(moveNoteBackward);
    singleCoverBackward = new QComboBox();
    wlist.append(new QLabel(tr("Cover single note ")));
    clist.append(singleCoverBackward);
    anyCoverBackward = new QComboBox();
    wlist.append(new QLabel(tr("Cover any notes ")));
    clist.append(anyCoverBackward);
    backward = ComboGroup(tr("Drag Backward"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(backward);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(moveNoteBackward);
    clist.append(singleCoverBackward);
    clist.append(anyCoverBackward);
    comboGroupManager(clist, slist, comboDefault);

    // 2.7 Drag Forward
    wlist.clear();
    clist.clear();
    moveNoteForward = new QComboBox();
    wlist.append(new QLabel(tr("Move notes followed ")));
    clist.append(moveNoteForward);
    stretchNoteForward = new QComboBox();
    wlist.append(new QLabel(tr("Stretch notes followed ")));
    clist.append(stretchNoteForward);
    addRestForward = new QComboBox();
    wlist.append(new QLabel(tr("Add rest note ")));
    clist.append(addRestForward);
    forward = ComboGroup(tr("Drag Forward"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(forward);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(moveNoteForward);
    clist.append(stretchNoteForward);
    clist.append(addRestForward);
    comboGroupManager(clist, slist, comboDefault);

    contentLayout->addSpacing(gap);

    // 3 Mouse
    mouse = new QLabel(tr("Mouse Click Modifier"));
    mouse->setFont(titleFont);
    mouse->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mouse->setStyleSheet(titleStyle);
    contentLayout->addWidget(mouse);

    slist.clear();
    slist.append(tr("Left Click"));
    slist.append(tr("Double Left Click"));
    slist.append(tr("Middle Click"));
    slist.append(tr("Double Middle Click"));
    slist.append(tr("Right Click"));
    slist.append(tr("Double Right Click"));
    slist.append(comboDefault);

    // 3.1 Mode2-Add
    wlist.clear();
    clist.clear();
    mode2_AddPoint = new QComboBox();
    wlist.append(new QLabel(tr("Add point ")));
    clist.append(mode2_AddPoint);
    mode2_Add = ComboGroup(tr("Mode2-Add"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(mode2_Add);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(mode2_AddPoint);
    comboGroupManager(clist, slist, comboDefault);

    // 3.2 Mode2-Modify
    wlist.clear();
    clist.clear();
    mode2_RemovePoint = new QComboBox();
    wlist.append(new QLabel(tr("Remove point ")));
    clist.append(mode2_RemovePoint);
    mode2_ChangeType = new QComboBox();
    wlist.append(new QLabel(tr("Change point type ")));
    clist.append(mode2_ChangeType);
    mode2_OpenMenu = new QComboBox();
    wlist.append(new QLabel(tr("Open point panel ")));
    clist.append(mode2_OpenMenu);
    mode2_Modify = ComboGroup(tr("Mode2-Modify"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(mode2_Modify);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(mode2_RemovePoint);
    clist.append(mode2_ChangeType);
    clist.append(mode2_OpenMenu);
    comboGroupManager(clist, slist, comboDefault);

    // 3.3 Envelope-Add
    wlist.clear();
    clist.clear();
    envelope_AddPoint = new QComboBox();
    wlist.append(new QLabel(tr("Add point ")));
    clist.append(envelope_AddPoint);
    envelope_Add = ComboGroup(tr("Envelope-Add"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(envelope_Add);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(envelope_AddPoint);
    comboGroupManager(clist, slist, comboDefault);

    // 3.4 Envelope-Modify
    wlist.clear();
    clist.clear();
    envelope_RemovePoint = new QComboBox();
    wlist.append(new QLabel(tr("Remove point ")));
    clist.append(envelope_RemovePoint);
    envelope_Standardize = new QComboBox();
    wlist.append(new QLabel(tr("Standardize the point ")));
    clist.append(envelope_Standardize);
    envelope_OpenMenu = new QComboBox();
    wlist.append(new QLabel(tr("Open point panel ")));
    clist.append(envelope_OpenMenu);
    envelope_Modify = ComboGroup(tr("Envelope-Modify"), wlist, clist, textFont);

    wlist.clear();
    wlist.append(envelope_Modify);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    clist.clear();
    clist.append(envelope_RemovePoint);
    clist.append(envelope_Standardize);
    clist.append(envelope_OpenMenu);
    comboGroupManager(clist, slist, comboDefault);

    contentLayout->addSpacing(gap);

    // 4 Render
    render = new QLabel(tr("Render"));
    render->setFont(titleFont);
    render->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    render->setStyleSheet(titleStyle);
    contentLayout->addWidget(render);

    notBase64 = new QCheckBox(tr("Don't use Base64 encoding"));
    notBase64->setFont(textFont);
    notBase64->setStyleSheet(indent);
    contentLayout->addWidget(notBase64);

    notCMD = new QCheckBox(tr("Don't use Command Prompt (CMD)"));
    notCMD->setFont(textFont);
    notCMD->setStyleSheet(indent);
    contentLayout->addWidget(notCMD);

    slist.clear();
    slist.append("1");
    slist.append("2");
    slist.append("3");
    slist.append("4");
    slist.append("5");
    slist.append("6");
    slist.append("7");
    slist.append("8");
    slist.append("9");
    slist.append("10");
    slist.append("11");
    slist.append("12");
    threadNum = new QComboBox();
    threadNum->addItems(slist);
    wlist.clear();
    tmpWidget = new QLabel(tr("Threads for rendering: "));
    wlist.append(tmpWidget);
    wlist.append(threadNum);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    connect(notCMD, &QCheckBox::toggled, threadNum, &QWidget::setEnabled);
    connect(notCMD, &QCheckBox::toggled, tmpWidget, &QWidget::setEnabled);
    threadNum->setEnabled(false);
    tmpWidget->setEnabled(false);

    contentLayout->addSpacing(gap);

    // 5 Cache
    cache = new QLabel(tr("Cache"));
    cache->setFont(titleFont);
    cache->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    cache->setStyleSheet(titleStyle);
    contentLayout->addWidget(cache);

    noCache = new QCheckBox(tr("No Cache"));
    noCache->setFont(textFont);
    noCache->setStyleSheet(indent);
    contentLayout->addWidget(noCache);

    // 5.1 Clear
    noClear = new QRadioButton(tr("No clear"));
    clearOnFileClose = new QRadioButton(tr("Clear on file close"));
    clearOnWindowClose = new QRadioButton(tr("Clear on window close"));
    clearWhenFull = new QRadioButton(tr("Clear prior cache when more than "));
    cacheCapacity = new QSpinBox();
    cacheCapacity->setMinimum(0);
    cacheCapacity->setMaximum(999999);
    cacheCapacity->setStyleSheet("QSpinBox { border:1px solid lightgray; } "
                                 "QSpinBox::up-button, QSpinBox::down-button { width:0px; }");

    tmpVLayout = new QVBoxLayout();
    tmpVLayout->setMargin(0);

    wlist.clear();
    wlist.append(noClear);
    wlist.append(clearOnFileClose);
    wlist.append(clearOnWindowClose);
    for (QWidget *w : wlist) {
        w->setFont(textFont);
        w->setStyleSheet(indent);
        tmpVLayout->addWidget(w);
    }
    wlist.clear();
    wlist.append(clearWhenFull);
    wlist.append(cacheCapacity);
    wlist.append(new QLabel("MB"));
    tmpVLayout->addLayout(HLayout(wlist, textFont, padding));
    tmpVLayout->addSpacing(10);

    cacheClear = new QGroupBox(tr("Clear"));
    cacheClear->setLayout(tmpVLayout);

    wlist.clear();
    wlist.append(cacheClear);
    contentLayout->addLayout(HLayout(wlist, textFont, padding));

    connect(noCache, &QCheckBox::toggled, cacheClear, &QGroupBox::setDisabled);
    cacheClear->setDisabled(false);
    connect(clearWhenFull, &QRadioButton::toggled, cacheCapacity, &QSpinBox::setEnabled);
    cacheCapacity->setEnabled(false);

    contentLayout->addSpacing(gap);

    // set content widget
    settingContent = new QWidget(this);
    settingContent->setLayout(contentLayout);
    mainScroll->setWidget(settingContent);

    // connect manager
    navigateConnectManager();
    editConnectManager();

    // history index
    historyIndex = 0;
    savedHistoryIndex = 0;
    historyBlock = false;
    historyLink = false;
}

SettingTab::~SettingTab() {
    clearHistory();
}

QHBoxLayout *SettingTab::HLayout(const QList<QWidget *> &list, const QFont &font, int space) {
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);

    layout->addSpacing(space);
    for (QWidget *w : list) {
        w->setFont(font);
        layout->addWidget(w);
    }
    layout->addSpacerItem(new QSpacerItem(120, 0, QSizePolicy::Expanding));

    return layout;
}

QVBoxLayout *SettingTab::NavigateLayout(const QList<QToolButton *> &list, const QFont &font,
                                        const QString &itemStyle) {
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);

    layout->addSpacing(10);
    for (QToolButton *w : list) {
        w->setAutoRaise(true);
        w->setFont(font);
        w->setStyleSheet(itemStyle);

        QHBoxLayout *item = new QHBoxLayout();
        item->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Expanding));
        item->addWidget(w);
        item->addSpacing(60);

        layout->addLayout(item);
    }
    layout->addSpacerItem(new QSpacerItem(0, 10, QSizePolicy::Preferred, QSizePolicy::Expanding));

    return layout;
}
QGroupBox *SettingTab::ComboGroup(const QString &name, const QList<QWidget *> &wlist,
                                  const QList<QComboBox *> &clist, const QFont &font) {
    QGridLayout *groupLayout = new QGridLayout();
    groupLayout->setMargin(0);

    groupLayout->addItem(new QSpacerItem(60, 0), 0, 0);
    int wlen = wlist.size();
    for (int i = 0; i < wlen; i++) {
        wlist[i]->setFont(font);
        groupLayout->addWidget(wlist[i], i, 1);
    }
    int clen = clist.size();
    for (int i = 0; i < clen; i++) {
        clist[i]->setFont(font);
        groupLayout->addWidget(clist[i], i, 2);
    }
    groupLayout->addItem(new QSpacerItem(120, 0, QSizePolicy::Expanding), 0, 3);
    int bottom = wlen > clen ? wlen : clen;
    groupLayout->addItem(new QSpacerItem(0, 10), bottom, 0);

    QGroupBox *group = new QGroupBox(name);
    group->setLayout(groupLayout);

    return group;
}

void SettingTab::comboGroupManager(const QList<QComboBox *> &clist, const QStringList &slist,
                                   const QString &defaultText) {
    for (QComboBox *ori : clist) {
        ori->addItems(slist);
        connect(ori, &QComboBox::currentTextChanged, [=](const QString &text) {
            if (text == defaultText)
                return;

            bool tmpFlag = historyLink;
            historyLink = true;
            for (QComboBox *c : clist) {
                if (c == ori)
                    continue;
                if (c->currentText() == text) {
                    c->setCurrentText(defaultText);
                    break;
                }
            }
            historyLink = tmpFlag;
        });
    }
}

void SettingTab::navigateConnectManager() {
    QScrollBar *bar = mainScroll->verticalScrollBar();

    connect(toEdit, &QToolButton::clicked, [=]() { bar->setValue(edit->pos().y()); });
    connect(toKeyboard, &QToolButton::clicked, [=]() { bar->setValue(keyboard->pos().y()); });
    connect(toMouse, &QToolButton::clicked, [=]() { bar->setValue(mouse->pos().y()); });
    connect(toRender, &QToolButton::clicked, [=]() { bar->setValue(render->pos().y()); });
    connect(toCache, &QToolButton::clicked, [=]() { bar->setValue(cache->pos().y()); });
}

void SettingTab::editConnectManager() {
    // 1 Edit
    connect(propertyClear, &QCheckBox::clicked,
            [=](const QJsonValue &val) { setEditState(Edit, "propertyClear", val); });
    connect(batchMove, &QCheckBox::clicked,
            [=](const QJsonValue &val) { setEditState(Edit, "batchMove", val); });

    // 2 Keyboard
    // 2.1 Wheel
    connect(HZoom, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "HZoom", val); });
    connect(VZoom, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "VZoom", val); });
    connect(HMove, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "HMove", val); });
    connect(VMove, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "VMove", val); });
    // 2.2 Drag
    connect(pageDrag, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "pageDrag", val); });
    connect(regionSelect, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "regionSelect", val); });
    connect(addPointForward, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "addPointForward", val); });
    // 2.3 Mode2
    connect(mode2_HAttach, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "mode2_HAttach", val); });
    connect(mode2_VAttach, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "mode2_VAttach", val); });
    connect(mode2_CAttach, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "mode2_CAttach", val); });
    // 2.4 Envelope
    connect(envelope_HAttach, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "envelope_HAttach", val); });
    connect(envelope_VAttach, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "envelope_VAttach", val); });
    connect(envelope_CAttach, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "envelope_CAttach", val); });
    // 2.5 Right Click
    connect(defaultMenu, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "defaultMenu", val); });
    connect(pluginMenu, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "pluginMenu", val); });
    connect(sampleMenu, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "sampleMenu", val); });
    connect(toolMenu, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "toolMenu", val); });
    connect(immRender, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "immRender", val); });
    // 2.6 Backward
    connect(moveNoteBackward, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "moveNoteBackward", val); });
    connect(singleCoverBackward, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "singleCoverBackward", val); });
    connect(anyCoverBackward, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "anyCoverBackward", val); });
    // 2.7 Forward
    connect(moveNoteForward, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "moveNoteForward", val); });
    connect(stretchNoteForward, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "stretchNoteForward", val); });
    connect(addRestForward, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(KeyBoard, "addRestForward", val); });

    // 3 Mouse
    // 3.1 Mode2-Add
    connect(mode2_AddPoint, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Mouse, "mode2_AddPoint", val); });
    // 3.2 Mode2-Modify
    connect(mode2_RemovePoint, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Mouse, "mode2_RemovePoint", val); });
    connect(mode2_ChangeType, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Mouse, "mode2_ChangeType", val); });
    connect(mode2_OpenMenu, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Mouse, "mode2_OpenMenu", val); });
    // 3.3 Envelope-Add
    connect(envelope_AddPoint, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Mouse, "envelope_AddPoint", val); });
    // 3.4 Envelope-Modify
    connect(envelope_RemovePoint, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Mouse, "envelope_RemovePoint", val); });
    connect(envelope_Standardize, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Mouse, "envelope_Standardize", val); });
    connect(envelope_RemovePoint, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Mouse, "envelope_RemovePoint", val); });

    // 4 Render
    connect(notBase64, &QCheckBox::clicked,
            [=](const QJsonValue &val) { setEditState(Render, "notBase64", val); });
    connect(notCMD, &QCheckBox::clicked,
            [=](const QJsonValue &val) { setEditState(Render, "notCMD", val); });
    connect(threadNum, &QComboBox::currentTextChanged,
            [=](const QJsonValue &val) { setEditState(Render, "threadNum", val); });

    // 5 Cache
    connect(noCache, &QCheckBox::clicked,
            [=](const QJsonValue &val) { setEditState(Cache, "noCache", val); });
    // 5.1 Clear
    connect(noClear, &QRadioButton::clicked,
            [=]() { setEditState(Cache, "cacheClear", "noClear"); });
    connect(clearOnFileClose, &QRadioButton::clicked,
            [=]() { setEditState(Cache, "cacheClear", "clearOnFileClose"); });
    connect(clearOnWindowClose, &QRadioButton::clicked,
            [=]() { setEditState(Cache, "cacheClear", "clearOnWindowClose"); });
    connect(clearWhenFull, &QRadioButton::clicked,
            [=]() { setEditState(Cache, "cacheClear", "clearWhenFull"); });
    connect(cacheCapacity, &QSpinBox::editingFinished,
            [=]() { setEditState(Cache, "cacheCapacity", cacheCapacity->value()); });
}

void SettingTab::setEditState(const SettingType type, const QString &key, const QJsonValue &val) {
    QString sType = settingTypeToString(type);
    QJsonObject obj = settingObj.value(sType).toObject();

    if (!historyBlock) {
        if (historyLink) {
            opQueue = new SettingOperation(type, key, obj.value(key), val, opQueue);
        } else {
            addHistory(new SettingOperation(type, key, obj.value(key), val, opQueue));
            opQueue = nullptr;
        }
    }

    obj.remove(key);
    obj.insert(key, val);
    settingObj.remove(sType);
    settingObj.insert(sType, QJsonValue(obj));

    setEdited(true);
    updateMenuCore();
}

bool SettingTab::load() {
    QString filename = m_filename;
    if (!parseFile(filename)) {
        getDefaultSettings(filename);
        if (!parseFile(filename))
            return false;
    }

    // history ini
    historyList.clear();
    historyIndex = 0;
    savedHistoryIndex = 0;
    historyBlock = false;
    historyLink = false;

    setEdited(false);
    updateMenuCore();

    return true;
}

bool SettingTab::parseFile(const QString &filename) {
    // read file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray byteArray = file.readAll();

    // parse json
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(byteArray, &parseError);
    if (doc.isNull() || parseError.error != QJsonParseError::NoError) {
        qDebug() << "Parse error!";
        return false;
    }

    // set states
    bool f_parse = true;
    if (f_parse &= doc.isObject()) {
        settingObj = doc.object();
        // 1 Edit
        if (f_parse &= settingObj.contains("Edit")) {
            QJsonValue value = settingObj.value("Edit");
            if (f_parse &= value.isObject()) {
                QJsonObject obj = value.toObject();

                if (f_parse &= obj.contains("propertyClear")) {
                    QJsonValue val = obj.value("propertyClear");
                    if (f_parse &= val.isBool()) {
                        propertyClear->setChecked(val.toBool());
                    }
                }
                if (f_parse &= obj.contains("batchMove")) {
                    QJsonValue val = obj.value("batchMove");
                    if (f_parse &= val.isBool()) {
                        batchMove->setChecked(val.toBool());
                    }
                }
            }
        }

        // 2 KeyBoard
        if (f_parse &= settingObj.contains("KeyBoard")) {
            QJsonValue value = settingObj.value("KeyBoard");
            if (f_parse &= value.isObject()) {
                QJsonObject obj = value.toObject();

                // 2.1 Wheel
                if (f_parse &= obj.contains("HZoom")) {
                    QJsonValue val = obj.value("HZoom");
                    if (f_parse &= val.isString()) {
                        HZoom->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("VZoom")) {
                    QJsonValue val = obj.value("VZoom");
                    if (f_parse &= val.isString()) {
                        VZoom->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("HMove")) {
                    QJsonValue val = obj.value("HMove");
                    if (f_parse &= val.isString()) {
                        HMove->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("VMove")) {
                    QJsonValue val = obj.value("VMove");
                    if (f_parse &= val.isString()) {
                        VMove->setCurrentText(val.toString());
                    }
                }

                // 2.2 Drag
                if (f_parse &= obj.contains("pageDrag")) {
                    QJsonValue val = obj.value("pageDrag");
                    if (f_parse &= val.isString()) {
                        pageDrag->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("regionSelect")) {
                    QJsonValue val = obj.value("regionSelect");
                    if (f_parse &= val.isString()) {
                        regionSelect->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("addPointForward")) {
                    QJsonValue val = obj.value("addPointForward");
                    if (f_parse &= val.isString()) {
                        addPointForward->setCurrentText(val.toString());
                    }
                }

                // 2.3 Mode2
                if (f_parse &= obj.contains("mode2_HAttach")) {
                    QJsonValue val = obj.value("mode2_HAttach");
                    if (f_parse &= val.isString()) {
                        mode2_HAttach->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("mode2_VAttach")) {
                    QJsonValue val = obj.value("mode2_VAttach");
                    if (f_parse &= val.isString()) {
                        mode2_VAttach->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("mode2_CAttach")) {
                    QJsonValue val = obj.value("mode2_CAttach");
                    if (f_parse &= val.isString()) {
                        mode2_CAttach->setCurrentText(val.toString());
                    }
                }

                // 2.4 Envelope
                if (f_parse &= obj.contains("envelope_HAttach")) {
                    QJsonValue val = obj.value("envelope_HAttach");
                    if (f_parse &= val.isString()) {
                        envelope_HAttach->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("envelope_VAttach")) {
                    QJsonValue val = obj.value("envelope_VAttach");
                    if (f_parse &= val.isString()) {
                        envelope_VAttach->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("envelope_CAttach")) {
                    QJsonValue val = obj.value("envelope_CAttach");
                    if (f_parse &= val.isString()) {
                        envelope_CAttach->setCurrentText(val.toString());
                    }
                }

                // 2.5 Right Click
                if (f_parse &= obj.contains("defaultMenu")) {
                    QJsonValue val = obj.value("defaultMenu");
                    if (f_parse &= val.isString()) {
                        defaultMenu->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("pluginMenu")) {
                    QJsonValue val = obj.value("pluginMenu");
                    if (f_parse &= val.isString()) {
                        pluginMenu->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("sampleMenu")) {
                    QJsonValue val = obj.value("sampleMenu");
                    if (f_parse &= val.isString()) {
                        sampleMenu->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("toolMenu")) {
                    QJsonValue val = obj.value("toolMenu");
                    if (f_parse &= val.isString()) {
                        toolMenu->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("immRender")) {
                    QJsonValue val = obj.value("immRender");
                    if (f_parse &= val.isString()) {
                        immRender->setCurrentText(val.toString());
                    }
                }

                // 2.6 Backward
                if (f_parse &= obj.contains("moveNoteBackward")) {
                    QJsonValue val = obj.value("moveNoteBackward");
                    if (f_parse &= val.isString()) {
                        moveNoteBackward->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("singleCoverBackward")) {
                    QJsonValue val = obj.value("singleCoverBackward");
                    if (f_parse &= val.isString()) {
                        singleCoverBackward->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("anyCoverBackward")) {
                    QJsonValue val = obj.value("anyCoverBackward");
                    if (f_parse &= val.isString()) {
                        anyCoverBackward->setCurrentText(val.toString());
                    }
                }

                // 2.7 Forward
                if (f_parse &= obj.contains("moveNoteForward")) {
                    QJsonValue val = obj.value("moveNoteForward");
                    if (f_parse &= val.isString()) {
                        moveNoteForward->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("stretchNoteForward")) {
                    QJsonValue val = obj.value("stretchNoteForward");
                    if (f_parse &= val.isString()) {
                        stretchNoteForward->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("addRestForward")) {
                    QJsonValue val = obj.value("addRestForward");
                    if (f_parse &= val.isString()) {
                        addRestForward->setCurrentText(val.toString());
                    }
                }
            }
        }

        // 3 Mouse
        if (f_parse &= settingObj.contains("Mouse")) {
            QJsonValue value = settingObj.value("Mouse");
            if (f_parse &= value.isObject()) {
                QJsonObject obj = value.toObject();

                // 3.1 Mode2-Add
                if (f_parse &= obj.contains("mode2_AddPoint")) {
                    QJsonValue val = obj.value("mode2_AddPoint");
                    if (f_parse &= val.isString()) {
                        mode2_AddPoint->setCurrentText(val.toString());
                    }
                }

                // 3.2 Mode2-Modify
                if (f_parse &= obj.contains("mode2_RemovePoint")) {
                    QJsonValue val = obj.value("mode2_RemovePoint");
                    if (f_parse &= val.isString()) {
                        mode2_RemovePoint->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("mode2_ChangeType")) {
                    QJsonValue val = obj.value("mode2_ChangeType");
                    if (f_parse &= val.isString()) {
                        mode2_ChangeType->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("mode2_OpenMenu")) {
                    QJsonValue val = obj.value("mode2_OpenMenu");
                    if (f_parse &= val.isString()) {
                        mode2_OpenMenu->setCurrentText(val.toString());
                    }
                }

                // 3.3 Envelope-Add
                if (f_parse &= obj.contains("envelope_AddPoint")) {
                    QJsonValue val = obj.value("envelope_AddPoint");
                    if (f_parse &= val.isString()) {
                        envelope_AddPoint->setCurrentText(val.toString());
                    }
                }

                // 3.4 Envelope-Modify
                if (f_parse &= obj.contains("envelope_RemovePoint")) {
                    QJsonValue val = obj.value("envelope_RemovePoint");
                    if (f_parse &= val.isString()) {
                        envelope_RemovePoint->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("envelope_Standardize")) {
                    QJsonValue val = obj.value("envelope_Standardize");
                    if (f_parse &= val.isString()) {
                        envelope_Standardize->setCurrentText(val.toString());
                    }
                }
                if (f_parse &= obj.contains("envelope_OpenMenu")) {
                    QJsonValue val = obj.value("envelope_OpenMenu");
                    if (f_parse &= val.isString()) {
                        envelope_OpenMenu->setCurrentText(val.toString());
                    }
                }
            }
        }

        // 4 Render
        if (f_parse &= settingObj.contains("Render")) {
            QJsonValue value = settingObj.value("Render");
            if (f_parse &= value.isObject()) {
                QJsonObject obj = value.toObject();

                if (f_parse &= obj.contains("notBase64")) {
                    QJsonValue val = obj.value("notBase64");
                    if (f_parse &= val.isBool()) {
                        notBase64->setChecked(val.toBool());
                    }
                }
                if (f_parse &= obj.contains("notCMD")) {
                    QJsonValue val = obj.value("notCMD");
                    if (f_parse &= val.isBool()) {
                        notCMD->setChecked(val.toBool());
                    }
                }
                if (f_parse &= obj.contains("threadNum")) {
                    QJsonValue val = obj.value("threadNum");
                    if (f_parse &= val.isString()) {
                        threadNum->setCurrentText(val.toString());
                    }
                }
            }
        }

        // 5 Cache
        if (f_parse &= settingObj.contains("Cache")) {
            QJsonValue value = settingObj.value("Cache");
            if (f_parse &= value.isObject()) {
                QJsonObject obj = value.toObject();

                if (f_parse &= obj.contains("noCache")) {
                    QJsonValue val = obj.value("noCache");
                    if (f_parse &= val.isBool()) {
                        noCache->setChecked(val.toBool());
                    }
                }

                // 5.1 Clear
                if (f_parse &= obj.contains("cacheClear")) {
                    QJsonValue val = obj.value("cacheClear");
                    if (f_parse &= val.isString()) {
                        QString str = val.toString();
                        if (str == "noClear") {
                            noClear->click();
                        } else if (str == "clearOnFileClose") {
                            clearOnFileClose->click();
                        } else if (str == "clearOnWindowClose") {
                            clearOnWindowClose->click();
                        } else if (str == "clearWhenFull") {
                            clearWhenFull->click();
                        } else {
                            f_parse = false;
                        }
                    }
                }
                if (f_parse &= obj.contains("cacheCapacity")) {
                    QJsonValue val = obj.value("cacheCapacity");
                    if (f_parse &= val.isDouble()) {
                        cacheCapacity->setValue(val.toInt());
                    }
                }
            }
        }
    }

    file.close();

    return f_parse;
}

void SettingTab::clearHistory() {
    for (int i = historyList.size() - 1; i >= 0; --i) {
        delete historyList.at(i);
    }
    historyList.clear();
    historyIndex = 0;
    savedHistoryIndex = -1;
}

bool SettingTab::save() {
    // open file
    QString filename = m_filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite)) {
        return false;
    }

    // write to file
    QJsonDocument doc;
    doc.setObject(settingObj);
    QByteArray byteArray = doc.toJson();
    file.write(byteArray);

    file.close();
    setEdited(false);
    savedHistoryIndex = historyIndex;
    emit settingsChanged();

    return true;
}

bool SettingTab::restore() {
    return false;
}

void SettingTab::awake() {
    CentralTab::awake();
}

void SettingTab::sleep() {
    CentralTab::sleep();
}

void SettingTab::enter() {
    CentralTab::enter();
}

void SettingTab::leave() {
    CentralTab::leave();
}

void SettingTab::setFixedname(const QString &value) {
    CentralTab::setFixedname(value);
    setTabName(value);
}

bool SettingTab::getDefaultSettings(const QString &filename) {
    // open file
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        return false;
    }

    // creat json object
    QJsonObject json;

    QJsonObject Edit;
    Edit.insert("propertyClear", false);
    Edit.insert("batchMove", true);
    json.insert("Edit", QJsonValue(Edit));

    QJsonObject KeyBoard;
    // Wheel
    KeyBoard.insert("HZoom", "Ctrl+Shift");
    KeyBoard.insert("VZoom", "Ctrl");
    KeyBoard.insert("HMove", "Shift");
    KeyBoard.insert("VMove", "None");
    // Drag
    KeyBoard.insert("pageDrag", "Ctrl+Shift");
    KeyBoard.insert("regionSelect", "Ctrl");
    KeyBoard.insert("addPointForward", "Shift");
    // Mode 2
    KeyBoard.insert("mode2_HAttach", "Shift");
    KeyBoard.insert("mode2_VAttach", "Ctrl+Shift");
    KeyBoard.insert("mode2_CAttach", "Ctrl");
    // Envelope
    KeyBoard.insert("envelope_HAttach", "Shift");
    KeyBoard.insert("envelope_VAttach", "Ctrl+Shift");
    KeyBoard.insert("envelope_CAttach", "Ctrl");
    // Right Click
    KeyBoard.insert("defaultMenu", "None");
    KeyBoard.insert("pluginMenu", "Ctrl+Shift");
    KeyBoard.insert("sampleMenu", "Shift");
    KeyBoard.insert("toolMenu", "Ctrl");
    KeyBoard.insert("immRender", "Alt");
    // Drag Backward
    KeyBoard.insert("moveNoteBackward", "None");
    KeyBoard.insert("singleCoverBackward", "Ctrl");
    KeyBoard.insert("anyCoverBackward", "Ctrl+Shift");
    // Drag Forward
    KeyBoard.insert("moveNoteForward", "None");
    KeyBoard.insert("stretchNoteForward", "Ctrl");
    KeyBoard.insert("addRestForward", "Ctrl+Shift");
    //
    json.insert("KeyBoard", QJsonValue(KeyBoard));

    QJsonObject Mouse;
    // Mode 2 - Add
    Mouse.insert("mode2_AddPoint", "Double Left Click");
    // Mode 2 - Modify
    Mouse.insert("mode2_RemovePoint", "Double Left Click");
    Mouse.insert("mode2_ChangeType", "Right Click");
    Mouse.insert("mode2_OpenMenu", "Middle Click");
    // Envelope - Add
    Mouse.insert("envelope_AddPoint", "Double Left Click");
    // Envelope - Modify
    Mouse.insert("envelope_RemovePoint", "Double Left Click");
    Mouse.insert("envelope_Standardize", "Right Click");
    Mouse.insert("envelope_OpenMenu", "Middle Click");
    //
    json.insert("Mouse", QJsonValue(Mouse));

    QJsonObject Render;
    Render.insert("notBase64", false);
    Render.insert("notCMD", false);
    Render.insert("threadNum", "1");
    json.insert("Render", QJsonValue(Render));

    QJsonObject Cache;
    Cache.insert("noCache", false);
    Cache.insert("cacheClear", "noClear");
    Cache.insert("cacheCapacity", 500);
    json.insert("Cache", QJsonValue(Cache));

    // write to file
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
    file.write(byteArray);

    file.close();
    return true;
}

void SettingTab::updateMenuRoot() {
    tabActions->setNaturalStatus();
    updateMenuCore();
}

void SettingTab::updateMenuCore() {
    tabActions->saveFile->setEnabled(edited);
    tabActions->restoreFile->setEnabled(edited);

    tabActions->undo->setEnabled(!earliest());
    tabActions->redo->setEnabled(!latest());
}
