QT       += core gui svg network xml multimedia concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Backend/Common/QControlPoint.cpp \
    Backend/Common/QGenonSettings.cpp \
    Backend/Common/QOtoSample.cpp \
    Backend/Common/QOtoSampleList.cpp \
    Backend/Document/Data/ConfigData.cpp \
    Backend/Document/Data/SequenceTextData.cpp \
    Backend/Document/Data/SettingIniData.cpp \
    Backend/Document/Data/ShortcutsData.cpp \
    Backend/Document/Directory/DirectoryCollect.cpp \
    Backend/Document/Directory/DirectoryManager.cpp \
    Backend/Document/Directory/PluginInfo.cpp \
    Backend/Document/Directory/PluginsCollect.cpp \
    Backend/Document/Directory/VoiceCollect.cpp \
    Backend/Document/Directory/VoiceInfo.cpp \
    Backend/Document/File/FileCollect.cpp \
    Backend/Document/File/FileManager.cpp \
    Backend/Document/File/NormalFile.cpp \
    Backend/Document/File/NormalFileCollect.cpp \
    Backend/Document/File/PlainTextFile.cpp \
    Backend/Document/File/SequenceTextFile.cpp \
    Backend/Document/File/SettingIniFile.cpp \
    Backend/Document/File/ShortcutsFile.cpp \
    Backend/Import/QFrequencyFile.cpp \
    Backend/Import/QMidiFile.cpp \
    Backend/Import/QPresampFile.cpp \
    Backend/Import/QSettingFile.cpp \
    Backend/Import/QSettingFiles/QSettingSection.cpp \
    Backend/Import/QSynthVFile.cpp \
    Backend/Import/QVocaloidFile.cpp \
    Backend/Import/QWaveInfo.cpp \
    Backend/Note/QLinkNote.cpp \
    Backend/Note/QNoteEnvelope.cpp \
    Backend/Note/QNoteMode2.cpp \
    Backend/Plugin/PluginHandler.cpp \
    Backend/Plugin/PluginTempData.cpp \
    Backend/Render/RenderArgs.cpp \
    Backend/Render/RenderUtils/UtaPitchCurves.cpp \
    Backend/Render/RenderUtils/UtaTranslator.cpp \
    Backend/Render/ResamplerArgs.cpp \
    Backend/Render/WavtoolArgs.cpp \
    Backend/VoiceBank/QOtoIni.cpp \
    Backend/VoiceBank/QOtoLevel.cpp \
    Backend/VoiceBank/QOtoReference.cpp \
    Backend/VoiceBank/QPrefixMap.cpp \
    Backend/VoiceBank/QReadmeText.cpp \
    Backend/VoiceBank/QVoiceBank.cpp \
    Frontend/Actions/BaseActionList.cpp \
    Frontend/Actions/KeyboardActionList.cpp \
    Frontend/Actions/SettingActionList.cpp \
    Frontend/Actions/TuningActionList.cpp \
    Frontend/Actions/VoiceActionList.cpp \
    Frontend/Actions/WelcomeActionList.cpp \
    Frontend/Common/Graphics/GraphicsArea.cpp \
    Frontend/Common/Graphics/GraphicsDragger.cpp \
    Frontend/Common/Graphics/GraphicsHandle.cpp \
    Frontend/Common/Graphics/GraphicsLineEdit.cpp \
    Frontend/Common/Graphics/GraphicsLineHandle.cpp \
    Frontend/Common/Graphics/GraphicsLinearView.cpp \
    Frontend/Common/Graphics/GraphicsPlaneHandle.cpp \
    Frontend/Common/MoreWidget.cpp \
    Frontend/Common/Operation.cpp \
    Frontend/Common/TabWidget.cpp \
    Frontend/Common/Utils/MorePoint.cpp \
    Frontend/Common/Utils/MoreSize.cpp \
    Frontend/Controls/ComboControl.cpp \
    Frontend/Controls/CustomControls.cpp \
    Frontend/Controls/FixedComboBox.cpp \
    Frontend/Controls/FixedLineEdit.cpp \
    Frontend/Controls/FixedSpinBox.cpp \
    Frontend/Controls/FixedTextEdit.cpp \
    Frontend/Controls/LineControl.cpp \
    Frontend/Controls/SlideControl.cpp \
    Frontend/Controls/SlideLineControl.cpp \
    Frontend/Controls/SwitchButton.cpp \
    Frontend/Controls/SwitchButtons/SwitchButtonGroup.cpp \
    Frontend/Controls/SwitchButtons/SwitchButtonUnderline.cpp \
    Frontend/Controls/TextControl.cpp \
    Frontend/Customs/LinearScrollArea.cpp \
    Frontend/Customs/TransparentContainer.cpp \
    Frontend/Dialogs/BackstageDialog.cpp \
    Frontend/Dialogs/BackstageDialogs/BaseWork.cpp \
    Frontend/Dialogs/BackstageDialogs/ConcatenateWork.cpp \
    Frontend/Dialogs/BackstageDialogs/ResampleWork.cpp \
    Frontend/Dialogs/BaseDialog.cpp \
    Frontend/Dialogs/ExecutePluginDialog.cpp \
    Frontend/Dialogs/InputDialog.cpp \
    Frontend/Dialogs/InsertLyricsDialog.cpp \
    Frontend/Dialogs/NotePropertiesDialog.cpp \
    Frontend/Dialogs/ProjectSettingsDialog.cpp \
    Frontend/Dialogs/ScriptPluginDialog.cpp \
    Frontend/Dialogs/SelectsDialog.cpp \
    Frontend/Dialogs/TerminalDialog.cpp \
    Frontend/Singletons/CentralTabWidget.cpp \
    Frontend/Singletons/ColorTheme.cpp \
    Frontend/Singletons/ComboSelector.cpp \
    Frontend/Singletons/EventHandler.cpp \
    Frontend/Singletons/TempHandler.cpp \
    Frontend/Tabs/BaseTab.cpp \
    Frontend/Tabs/CentralTab.cpp \
    Frontend/Tabs/KeyboardTab.cpp \
    Frontend/Tabs/KeyboardTabs/KeyLabelContent.cpp \
    Frontend/Tabs/KeyboardTabs/KeyLineEdit.cpp \
    Frontend/Tabs/KeyboardTabs/KeyModifyWidget.cpp \
    Frontend/Tabs/KeyboardTabs/KeyTableWidget.cpp \
    Frontend/Tabs/KeyboardTabs/KeyboardTabContent.cpp \
    Frontend/Tabs/KeyboardTabs/KeyboardTab_Edit.cpp \
    Frontend/Tabs/KeyboardTabs/Operations/KeyOperation.cpp \
    Frontend/Tabs/SettingTab.cpp \
    Frontend/Tabs/SettingTabs/Operations/SettingOperation.cpp \
    Frontend/Tabs/SettingTabs/SettingTab_Edit.cpp \
    Frontend/Tabs/TuningTab.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesArea.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Actions.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Adjust.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Assist.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Associate.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Const.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Core.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Drag.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Draw.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Events.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Lyric.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Modify.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Move.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Operation.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Paste.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Play.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Properties.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Render.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Select.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_States.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Update.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesAreas/NotesArea_Variate.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/PianoArea.cpp \
    Frontend/Tabs/TuningTabs/Areas/Editor/SectionsArea.cpp \
    Frontend/Tabs/TuningTabs/Areas/Params/LiftersArea.cpp \
    Frontend/Tabs/TuningTabs/Areas/Params/LiftersAreas/LiftersArea_Adjust.cpp \
    Frontend/Tabs/TuningTabs/Areas/Params/LiftersAreas/LiftersArea_Move.cpp \
    Frontend/Tabs/TuningTabs/Areas/Params/LiftersAreas/LiftersArea_Properties.cpp \
    Frontend/Tabs/TuningTabs/Areas/Params/LiftersAreas/LiftersArea_States.cpp \
    Frontend/Tabs/TuningTabs/Areas/Params/ParamsDialArea.cpp \
    Frontend/Tabs/TuningTabs/Areas/Tracks/BlocksArea.cpp \
    Frontend/Tabs/TuningTabs/Areas/Tracks/HeadsArea.cpp \
    Frontend/Tabs/TuningTabs/Areas/Tracks/HeadsAreas/HeadsArea_Operations.cpp \
    Frontend/Tabs/TuningTabs/Areas/Tracks/HeadsAreas/HeadsArea_Reload.cpp \
    Frontend/Tabs/TuningTabs/Forms/BaseForm.cpp \
    Frontend/Tabs/TuningTabs/Forms/EditorForm.cpp \
    Frontend/Tabs/TuningTabs/Forms/EditorForms/EditorForm_ContextMenu.cpp \
    Frontend/Tabs/TuningTabs/Forms/ParamsForm.cpp \
    Frontend/Tabs/TuningTabs/Forms/TracksForm.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifter.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifters/GraphicsLifter_Assist.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifters/GraphicsLifter_Events.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifters/GraphicsLifter_Link.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifters/GraphicsLifter_Paint.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifters/GraphicsLifter_Properties.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifters/GraphicsLifter_States.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifters/GraphicsLifter_Variate.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLines.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNote.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_Adjust.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_Assist.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_ContextMenu.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_Events.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_Link.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_Paint.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_Properties.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_States.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_Update.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNotes/GraphicsNote_Values.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsPlayHead.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsPoint.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsPoints/GraphicsPoint_Events.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsPoints/GraphicsPoint_Link.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsPoints/GraphicsPoint_Properties.cpp \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsRubber.cpp \
    Frontend/Tabs/TuningTabs/Graphics/VibratoHandles/VibratoBaseHandle.cpp \
    Frontend/Tabs/TuningTabs/Graphics/VibratoHandles/VibratoLineHandle.cpp \
    Frontend/Tabs/TuningTabs/Graphics/VibratoHandles/VibratoPlaneHandle.cpp \
    Frontend/Tabs/TuningTabs/Graphics/VolumePoint.cpp \
    Frontend/Tabs/TuningTabs/Handlers/DraggerHandler.cpp \
    Frontend/Tabs/TuningTabs/Handlers/EnvelopeHandler.cpp \
    Frontend/Tabs/TuningTabs/Handlers/EnvelopeHandlers/EnvelopeHandler_Assist.cpp \
    Frontend/Tabs/TuningTabs/Handlers/EnvelopeHandlers/EnvelopeHandler_Paint.cpp \
    Frontend/Tabs/TuningTabs/Handlers/EnvelopeHandlers/EnvelopeHandler_States.cpp \
    Frontend/Tabs/TuningTabs/Handlers/EnvelopeHandlers/EnvelopeHandler_Variate.cpp \
    Frontend/Tabs/TuningTabs/Handlers/Mode2Handler.cpp \
    Frontend/Tabs/TuningTabs/Handlers/Mode2Handlers/Mode2Handler_Assist.cpp \
    Frontend/Tabs/TuningTabs/Handlers/Mode2Handlers/Mode2Handler_Paint.cpp \
    Frontend/Tabs/TuningTabs/Handlers/Mode2Handlers/Mode2Handler_States.cpp \
    Frontend/Tabs/TuningTabs/Handlers/Mode2Handlers/Mode2Handler_Variate.cpp \
    Frontend/Tabs/TuningTabs/Handlers/ScopeHandler.cpp \
    Frontend/Tabs/TuningTabs/Handlers/ScopeHandlers/ScopeHandler_Assist.cpp \
    Frontend/Tabs/TuningTabs/Handlers/ScopeHandlers/ScopeHandler_Core.cpp \
    Frontend/Tabs/TuningTabs/Handlers/ScopeHandlers/ScopeHandler_Move.cpp \
    Frontend/Tabs/TuningTabs/Handlers/ScopeHandlers/ScopeHandler_Properties.cpp \
    Frontend/Tabs/TuningTabs/Handlers/ScopeHandlers/ScopeHandler_States.cpp \
    Frontend/Tabs/TuningTabs/Handlers/ScopeHandlers/ScopeHandler_Variate.cpp \
    Frontend/Tabs/TuningTabs/Handlers/VibratoHandlers/VibratoHandler_Adjust.cpp \
    Frontend/Tabs/TuningTabs/Handlers/VibratoHandlers/VibratoHandler_Coordinate.cpp \
    Frontend/Tabs/TuningTabs/Handlers/VibratoHandlers/VibratoHandler_Core.cpp \
    Frontend/Tabs/TuningTabs/Handlers/VibratoHandlers/VibratoHandler_Paint.cpp \
    Frontend/Tabs/TuningTabs/Handlers/VibratoHandlers/VibratoHandler_Properties.cpp \
    Frontend/Tabs/TuningTabs/Interfaces/BaseInterface.cpp \
    Frontend/Tabs/TuningTabs/Interfaces/EditorInterface.cpp \
    Frontend/Tabs/TuningTabs/Interfaces/EditorInterfaces/EditorInterface_Call.cpp \
    Frontend/Tabs/TuningTabs/Interfaces/EditorInterfaces/EditorInterface_Link.cpp \
    Frontend/Tabs/TuningTabs/Interfaces/ParamsInterface.cpp \
    Frontend/Tabs/TuningTabs/Interfaces/TrackInterfaces/TracksInterface_ContextMenu.cpp \
    Frontend/Tabs/TuningTabs/Interfaces/TrackInterfaces/TracksInterface_Default.cpp \
    Frontend/Tabs/TuningTabs/Interfaces/TracksInterface.cpp \
    Frontend/Tabs/TuningTabs/Modules/Buttons/EnvButtonGroup.cpp \
    Frontend/Tabs/TuningTabs/Modules/Buttons/PlayButtonGroup.cpp \
    Frontend/Tabs/TuningTabs/Modules/Buttons/TrackButton.cpp \
    Frontend/Tabs/TuningTabs/Modules/Elements/PianoKey.cpp \
    Frontend/Tabs/TuningTabs/Modules/Elements/SectionsLine.cpp \
    Frontend/Tabs/TuningTabs/Modules/Elements/TrackContent.cpp \
    Frontend/Tabs/TuningTabs/Modules/Elements/TrackHead.cpp \
    Frontend/Tabs/TuningTabs/Modules/Form/FormSplitter.cpp \
    Frontend/Tabs/TuningTabs/Modules/Form/FormTitleBar.cpp \
    Frontend/Tabs/TuningTabs/Scrolls/LiftersScrollArea.cpp \
    Frontend/Tabs/TuningTabs/Scrolls/NoneScrollArea.cpp \
    Frontend/Tabs/TuningTabs/Scrolls/NotesScrollArea.cpp \
    Frontend/Tabs/TuningTabs/Operations/ImplicitOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/LengthOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/LyricsOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/MoveOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/NoteOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/PointsOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/ProjectOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/PropsOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/ScatterOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/SequenceOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/TempoOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/TrackOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/TrackOperations/TrackModifyOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/TrackOperations/TrackSeqOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/TrackOperations/TrackSwitchOperation.cpp \
    Frontend/Tabs/TuningTabs/Operations/TuneOperation.cpp \
    Frontend/Tabs/TuningTabs/ProjectInfoHandler.cpp \
    Frontend/Tabs/TuningTabs/TuningGroup.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Core.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Edit.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Modify.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_NoteProperty.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Oto.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Play.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Plugin.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_ProjectSettings.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Properties.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Render.cpp \
    Frontend/Tabs/TuningTabs/TuningTab_Unchange.cpp \
    Frontend/Tabs/VoiceBankTab.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoDataAreas/OtoDataArea_Operation.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoDataArea.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoInfoArea.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoInfoAreas/OtoInfoArea_Avatar.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoInfoAreas/OtoInfoArea_Change.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoInfoAreas/OtoInfoArea_Operation.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoPlayerArea.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoVisionArea.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoVisionAreas/OtoVisionArea_Cursor.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoVisionAreas/OtoVisionArea_Handle.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoVisionAreas/OtoVisionArea_Operation.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoVisionAreas/OtoVisionArea_Scroll.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/VoiceBankArea.cpp \
    Frontend/Tabs/VoiceBankTabs/Areas/WaveformArea.cpp \
    Frontend/Tabs/VoiceBankTabs/Graphics/GraphicsOtoHandle.cpp \
    Frontend/Tabs/VoiceBankTabs/Modules/ImageLabel.cpp \
    Frontend/Tabs/VoiceBankTabs/Modules/PlayerLabel.cpp \
    Frontend/Tabs/VoiceBankTabs/Operations/NonOtoOperations/InfoTextOperation.cpp \
    Frontend/Tabs/VoiceBankTabs/Operations/NonOtoOperation.cpp \
    Frontend/Tabs/VoiceBankTabs/Operations/OtoOperation.cpp \
    Frontend/Tabs/VoiceBankTabs/Operations/NonOtoOperations/PrefixOperation.cpp \
    Frontend/Tabs/VoiceBankTabs/Operations/OtoOperations/OtoChangeOperation.cpp \
    Frontend/Tabs/VoiceBankTabs/Operations/OtoOperations/OtoMoveOperation.cpp \
    Frontend/Tabs/VoiceBankTabs/Operations/OtoOperations/OtoVariateOperation.cpp \
    Frontend/Tabs/VoiceBankTabs/Operations/VoiceOperation.cpp \
    Frontend/Tabs/VoiceBankTabs/Scrolls/WaveformScrollArea.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceBankGroup.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceBankTab_Core.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceBankTab_Edit.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceBankTab_Extern.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceBankTab_Oto.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceBankTab_Play.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceBankTab_Unchange.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/OtoTableTab.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/OtoTableTabs/OtoTableTab_Menu.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/OtoTableTabs/OtoTableTab_Properties.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/OtoTableTabs/OtoTableTab_Row.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/OtoTableTabs/OtoTableTab_Set.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/PrefixMapTab.cpp \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/TextBoxTab.cpp \
    Frontend/Tabs/WelcomeTab.cpp \
    Frontend/Tabs/WelcomeTabs/FileListWidget.cpp \
    Frontend/Tabs/WelcomeTabs/FileListWidgetItem.cpp \
    Frontend/Tabs/WelcomeTabs/WelcomeTabContent.cpp \
    Frontend/Templates/LabelButton.cpp \
    Frontend/Templates/TemporaryMenu.cpp \
    Frontend/Templates/VectorButton.cpp \
    Global/Macros.cpp \
    Global/Methods.cpp \
    Global/QUtils.cpp \
    Global/Types.cpp \
    Global/UTAU/QUtauUtils.cpp \
    Global/Utils/CharsetHandler.cpp \
    Global/Utils/FileNameSet.cpp \
    Global/Utils/ItemList.cpp \
    Global/Utils/Templates.cpp \
    Global/Variables.cpp \
    Main/Actions/common.cpp \
    Main/Actions/preview.cpp \
    Main/Actions/shortcuts.cpp \
    Main/Actions/special.cpp \
    Main/Actions/tuning.cpp \
    Main/Actions/voice.cpp \
    Main/Events/drag.cpp \
    Main/Events/window.cpp \
    Main/Exec/exec.cpp \
    Main/Exec/launch.cpp \
    Main/Exec/welcome.cpp \
    Main/Import/midi.cpp \
    Main/Import/synthv.cpp \
    Main/Import/vocaloid.cpp \
    Main/Menu/init.cpp \
    Main/Menu/reload.cpp \
    Main/Menu/trigger.cpp \
    Main/Modules/stylesheet.cpp \
    Main/Refresh/files.cpp \
    Main/Refresh/recent.cpp \
    Main/Refresh/status.cpp \
    Main/Static/abnormal.cpp \
    Main/Static/data.cpp \
    Main/Static/file.cpp \
    Main/Static/flow.cpp \
    Main/Static/instance.cpp \
    Main/Tabs/change.cpp \
    Main/Tabs/core.cpp \
    Main/Tabs/handlers.cpp \
    Main/Tabs/untitle.cpp \
    Main/application.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp \
    Main/resources.cpp \
    Main/total.cpp

HEADERS += \
    Backend/Common/QControlPoint.h \
    Backend/Common/QGenonSettings.h \
    Backend/Common/QOtoSample.h \
    Backend/Common/QOtoSampleList.h \
    Backend/Document/Data/ConfigData.h \
    Backend/Document/Data/SequenceTextData.h \
    Backend/Document/Data/SettingIniData.h \
    Backend/Document/Data/ShortcutsData.h \
    Backend/Document/Directory/DirectoryCollect.h \
    Backend/Document/Directory/DirectoryManager.h \
    Backend/Document/Directory/PluginInfo.h \
    Backend/Document/Directory/PluginsCollect.h \
    Backend/Document/Directory/VoiceCollect.h \
    Backend/Document/Directory/VoiceInfo.h \
    Backend/Document/File/FileCollect.h \
    Backend/Document/File/FileManager.h \
    Backend/Document/File/NormalFile.h \
    Backend/Document/File/NormalFileCollect.h \
    Backend/Document/File/PlainTextFile.h \
    Backend/Document/File/SequenceTextFile.h \
    Backend/Document/File/SettingIniFile.h \
    Backend/Document/File/ShortcutsFile.h \
    Backend/Document/QSFileData.h \
    Backend/Import/QFrequencyFile.h \
    Backend/Import/QMidiFile.h \
    Backend/Import/QPresampFile.h \
    Backend/Import/QSettingFile.h \
    Backend/Import/QSettingFiles/QSettingSection.h \
    Backend/Import/QSynthVFile.h \
    Backend/Import/QVocaloidFile.h \
    Backend/Import/QWaveInfo.h \
    Backend/Note/QLinkNote.h \
    Backend/Note/QNoteEnvelope.h \
    Backend/Note/QNoteMode2.h \
    Backend/Plugin/PluginHandler.h \
    Backend/Plugin/PluginTempData.h \
    Backend/Render/RenderArgs.h \
    Backend/Render/RenderUtils/UtaPitchCurves.h \
    Backend/Render/RenderUtils/UtaTranslator.h \
    Backend/Render/ResamplerArgs.h \
    Backend/Render/WavtoolArgs.h \
    Backend/VoiceBank/QOtoIni.h \
    Backend/VoiceBank/QOtoLevel.h \
    Backend/VoiceBank/QOtoReference.h \
    Backend/VoiceBank/QPrefixMap.h \
    Backend/VoiceBank/QReadmeText.h \
    Backend/VoiceBank/QVoiceBank.h \
    Frontend/Actions/BaseActionList.h \
    Frontend/Actions/KeyboardActionList.h \
    Frontend/Actions/SettingActionList.h \
    Frontend/Actions/TuningActionList.h \
    Frontend/Actions/VoiceActionList.h \
    Frontend/Actions/WelcomeActionList.h \
    Frontend/Common/Graphics/GraphicsArea.h \
    Frontend/Common/Graphics/GraphicsDragger.h \
    Frontend/Common/Graphics/GraphicsHandle.h \
    Frontend/Common/Graphics/GraphicsLineEdit.h \
    Frontend/Common/Graphics/GraphicsLineHandle.h \
    Frontend/Common/Graphics/GraphicsLinearView.h \
    Frontend/Common/Graphics/GraphicsPlaneHandle.h \
    Frontend/Common/MoreWidget.h \
    Frontend/Common/Operation.h \
    Frontend/Common/TabWidget.h \
    Frontend/Common/Utils/MorePoint.h \
    Frontend/Common/Utils/MoreSize.h \
    Frontend/Controls/ComboControl.h \
    Frontend/Controls/CustomControls.h \
    Frontend/Controls/FixedComboBox.h \
    Frontend/Controls/FixedLineEdit.h \
    Frontend/Controls/FixedSpinBox.h \
    Frontend/Controls/FixedTextEdit.h \
    Frontend/Controls/LineControl.h \
    Frontend/Controls/SlideControl.h \
    Frontend/Controls/SlideLineControl.h \
    Frontend/Controls/SwitchButton.h \
    Frontend/Controls/SwitchButtons/SwitchButtonGroup.h \
    Frontend/Controls/SwitchButtons/SwitchButtonUnderline.h \
    Frontend/Controls/TextControl.h \
    Frontend/Customs/LinearScrollArea.h \
    Frontend/Customs/TransparentContainer.h \
    Frontend/Dialogs/BackstageDialog.h \
    Frontend/Dialogs/BackstageDialogs/BaseWork.h \
    Frontend/Dialogs/BackstageDialogs/ConcatenateWork.h \
    Frontend/Dialogs/BackstageDialogs/ResampleWork.h \
    Frontend/Dialogs/BaseDialog.h \
    Frontend/Dialogs/ExecutePluginDialog.h \
    Frontend/Dialogs/InputDialog.h \
    Frontend/Dialogs/InsertLyricsDialog.h \
    Frontend/Dialogs/NotePropertiesDialog.h \
    Frontend/Dialogs/ProjectSettingsDialog.h \
    Frontend/Dialogs/ScriptPluginDialog.h \
    Frontend/Dialogs/SelectsDialog.h \
    Frontend/Dialogs/TerminalDialog.h \
    Frontend/QSActions.h \
    Frontend/QSTabs.h \
    Frontend/Singletons/CentralTabWidget.h \
    Frontend/Singletons/ColorTheme.h \
    Frontend/Singletons/ComboSelector.h \
    Frontend/Singletons/EventHandler.h \
    Frontend/Singletons/TempHandler.h \
    Frontend/Tabs/BaseTab.h \
    Frontend/Tabs/CentralTab.h \
    Frontend/Tabs/KeyboardTab.h \
    Frontend/Tabs/KeyboardTabs/KeyLabelContent.h \
    Frontend/Tabs/KeyboardTabs/KeyLineEdit.h \
    Frontend/Tabs/KeyboardTabs/KeyModifyWidget.h \
    Frontend/Tabs/KeyboardTabs/KeyTableWidget.h \
    Frontend/Tabs/KeyboardTabs/KeyboardTabContent.h \
    Frontend/Tabs/KeyboardTabs/Operations/KeyOperation.h \
    Frontend/Tabs/SettingTab.h \
    Frontend/Tabs/SettingTabs/Operations/SettingOperation.h \
    Frontend/Tabs/TuningTab.h \
    Frontend/Tabs/TuningTabs/Areas/Editor/NotesArea.h \
    Frontend/Tabs/TuningTabs/Areas/Editor/PianoArea.h \
    Frontend/Tabs/TuningTabs/Areas/Editor/SectionsArea.h \
    Frontend/Tabs/TuningTabs/Areas/Params/LiftersArea.h \
    Frontend/Tabs/TuningTabs/Areas/Params/ParamsDialArea.h \
    Frontend/Tabs/TuningTabs/Areas/Tracks/BlocksArea.h \
    Frontend/Tabs/TuningTabs/Areas/Tracks/HeadsArea.h \
    Frontend/Tabs/TuningTabs/Forms/BaseForm.h \
    Frontend/Tabs/TuningTabs/Forms/EditorForm.h \
    Frontend/Tabs/TuningTabs/Forms/ParamsForm.h \
    Frontend/Tabs/TuningTabs/Forms/TracksForm.h \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLifter.h \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsLines.h \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsNote.h \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsPlayHead.h \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsPoint.h \
    Frontend/Tabs/TuningTabs/Graphics/GraphicsRubber.h \
    Frontend/Tabs/TuningTabs/Graphics/VibratoHandles/VibratoBaseHandle.h \
    Frontend/Tabs/TuningTabs/Graphics/VibratoHandles/VibratoLineHandle.h \
    Frontend/Tabs/TuningTabs/Graphics/VibratoHandles/VibratoPlaneHandle.h \
    Frontend/Tabs/TuningTabs/Graphics/VolumePoint.h \
    Frontend/Tabs/TuningTabs/Handlers/DraggerHandler.h \
    Frontend/Tabs/TuningTabs/Handlers/EnvelopeHandler.h \
    Frontend/Tabs/TuningTabs/Handlers/Mode2Handler.h \
    Frontend/Tabs/TuningTabs/Handlers/ScopeHandler.h \
    Frontend/Tabs/TuningTabs/Interfaces/BaseInterface.h \
    Frontend/Tabs/TuningTabs/Interfaces/EditorInterface.h \
    Frontend/Tabs/TuningTabs/Interfaces/ParamsInterface.h \
    Frontend/Tabs/TuningTabs/Interfaces/TracksInterface.h \
    Frontend/Tabs/TuningTabs/Modules/Buttons/EnvButtonGroup.h \
    Frontend/Tabs/TuningTabs/Modules/Buttons/PlayButtonGroup.h \
    Frontend/Tabs/TuningTabs/Modules/Buttons/TrackButton.h \
    Frontend/Tabs/TuningTabs/Modules/Elements/PianoKey.h \
    Frontend/Tabs/TuningTabs/Modules/Elements/SectionsLine.h \
    Frontend/Tabs/TuningTabs/Modules/Elements/TrackContent.h \
    Frontend/Tabs/TuningTabs/Modules/Elements/TrackHead.h \
    Frontend/Tabs/TuningTabs/Modules/Form/FormSplitter.h \
    Frontend/Tabs/TuningTabs/Modules/Form/FormTitleBar.h \
    Frontend/Tabs/TuningTabs/Scrolls/LiftersScrollArea.h \
    Frontend/Tabs/TuningTabs/Scrolls/NoneScrollArea.h \
    Frontend/Tabs/TuningTabs/Scrolls/NotesScrollArea.h \
    Frontend/Tabs/TuningTabs/Operations/ImplicitOperation.h \
    Frontend/Tabs/TuningTabs/Operations/LengthOperation.h \
    Frontend/Tabs/TuningTabs/Operations/LyricsOperation.h \
    Frontend/Tabs/TuningTabs/Operations/MoveOperation.h \
    Frontend/Tabs/TuningTabs/Operations/NoteOperation.h \
    Frontend/Tabs/TuningTabs/Operations/PointsOperation.h \
    Frontend/Tabs/TuningTabs/Operations/ProjectOperation.h \
    Frontend/Tabs/TuningTabs/Operations/PropsOperation.h \
    Frontend/Tabs/TuningTabs/Operations/ScatterOperation.h \
    Frontend/Tabs/TuningTabs/Operations/SequenceOperation.h \
    Frontend/Tabs/TuningTabs/Operations/TempoOperation.h \
    Frontend/Tabs/TuningTabs/Operations/TrackOperation.h \
    Frontend/Tabs/TuningTabs/Operations/TrackOperations/TrackModifyOperation.h \
    Frontend/Tabs/TuningTabs/Operations/TrackOperations/TrackSeqOperation.h \
    Frontend/Tabs/TuningTabs/Operations/TrackOperations/TrackSwitchOperation.h \
    Frontend/Tabs/TuningTabs/Operations/TuneOperation.h \
    Frontend/Tabs/TuningTabs/ProjectInfoHandler.h \
    Frontend/Tabs/TuningTabs/TuningGroup.h \
    Frontend/Tabs/VoiceBankTab.h \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoDataArea.h \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoInfoArea.h \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoPlayerArea.h \
    Frontend/Tabs/VoiceBankTabs/Areas/OtoVisionArea.h \
    Frontend/Tabs/VoiceBankTabs/Areas/VoiceBankArea.h \
    Frontend/Tabs/VoiceBankTabs/Areas/WaveformArea.h \
    Frontend/Tabs/VoiceBankTabs/Graphics/GraphicsOtoHandle.h \
    Frontend/Tabs/VoiceBankTabs/Modules/ImageLabel.h \
    Frontend/Tabs/VoiceBankTabs/Modules/PlayerLabel.h \
    Frontend/Tabs/VoiceBankTabs/Operations/NonOtoOperations/InfoTextOperation.h \
    Frontend/Tabs/VoiceBankTabs/Operations/NonOtoOperation.h \
    Frontend/Tabs/VoiceBankTabs/Operations/OtoOperation.h \
    Frontend/Tabs/VoiceBankTabs/Operations/NonOtoOperations/PrefixOperation.h \
    Frontend/Tabs/VoiceBankTabs/Operations/OtoOperations/OtoChangeOperation.h \
    Frontend/Tabs/VoiceBankTabs/Operations/OtoOperations/OtoMoveOperation.h \
    Frontend/Tabs/VoiceBankTabs/Operations/OtoOperations/OtoVariateOperation.h \
    Frontend/Tabs/VoiceBankTabs/Operations/VoiceOperation.h \
    Frontend/Tabs/VoiceBankTabs/Scrolls/WaveformScrollArea.h \
    Frontend/Tabs/VoiceBankTabs/VoiceBankGroup.h \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/OtoTableTab.h \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/PrefixMapTab.h \
    Frontend/Tabs/VoiceBankTabs/VoiceTabs/TextBoxTab.h \
    Frontend/Tabs/WelcomeTab.h \
    Frontend/Tabs/WelcomeTabs/FileListWidget.h \
    Frontend/Tabs/WelcomeTabs/FileListWidgetItem.h \
    Frontend/Tabs/WelcomeTabs/WelcomeTabContent.h \
    Frontend/Templates/LabelButton.h \
    Frontend/Templates/TemporaryMenu.h \
    Frontend/Templates/VectorButton.h \
    Global/Macros.h \
    Global/Methods.h \
    Global/QUtils.h \
    Global/Types.h \
    Global/UTAU/QUtauConstants.h \
    Global/UTAU/QUtauStrings.h \
    Global/UTAU/QUtauUtils.h \
    Global/UTAU/Strings/UtaCharacterText.h \
    Global/UTAU/Strings/UtaFilenames.h \
    Global/UTAU/Strings/UtaPluginText.h \
    Global/UTAU/Strings/UtaProjectText.h \
    Global/UTAU/Strings/UtaSettingText.h \
    Global/Utils/CharsetHandler.h \
    Global/Utils/FileNameSet.h \
    Global/Utils/ItemList.h \
    Global/Utils/Templates.h \
    Global/Variables.h \
    Main/application.h \
    Main/mainwindow.h \
    Main/resources.h \
    Main/total.h

win32{
RC_FILE += \
    Resources/platforms/win/res.rc
}
unix{
}
macx{
ICON = Resources/platforms/mac/qsynth.icns
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/res.qrc

INCLUDEPATH += \
    Global \
    Global/UTAU \
    Backend \
    Backend/Common \
    Backend/Document \
    Frontend \
    Frontend/Common \
    Frontend/Singletons \
    Main \

TRANSLATIONS += \
    Resources/translations/qsynthesis_cn.ts
