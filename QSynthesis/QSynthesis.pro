QT       += core gui svg network xml multimedia concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Application/Managers/ClientManager.cpp \
    Application/Managers/ColorTheme.cpp \
    Application/Managers/DataManager.cpp \
    Application/Managers/DataManagers/DataManager_Keys.cpp \
    Application/Managers/MemoryManager.cpp \
    Application/Managers/PluginManager.cpp \
    Application/Managers/VoiceManager.cpp \
    Application/MiniSystem/MiniSystem.cpp \
    Application/MiniSystem/MiniSystemNotifier.cpp \
    Application/MiniSystem/MiniSystemWatcher.cpp \
    Application/MiniSystem/PathTree.cpp \
    Application/application.cpp \
    Backend/Base/BaseDirInfo.cpp \
    Backend/Base/BaseFile.cpp \
    Backend/Common/QOtoSample.cpp \
    Backend/Common/QOtoSampleList.cpp \
    Backend/Documents/DirInfos/PluginInfo.cpp \
    Backend/Documents/DirInfos/VoiceInfo.cpp \
    Backend/Documents/Files/ConfigFile.cpp \
    Backend/Documents/Files/SequenceTextFile.cpp \
    Backend/Documents/Files/SettingIniFile.cpp \
    Backend/Documents/Files/ShortcutsFile.cpp \
    Backend/Documents/Import/QFrequencyFile.cpp \
    Backend/Documents/Import/QMidiFile.cpp \
    Backend/Documents/Import/QPresampFile.cpp \
    Backend/Documents/Import/QSynthVFile.cpp \
    Backend/Documents/Import/QVocaloidFile.cpp \
    Backend/Documents/Import/QWaveInfo.cpp \
    Backend/Structures/Find/FindOption.cpp \
    Backend/Structures/Transfer/NoteProperties.cpp \
    Backend/Structures/Transfer/NoteReadonlys.cpp \
    Backend/Structures/Transfer/PluginTempData.cpp \
    Backend/Utils/QDumpFile.cpp \
    Backend/Utils/QFileSet.cpp \
    Backend/Utils/QSettingFile.cpp \
    Backend/Utils/QWavetool.cpp \
    Backend/VoiceBank/QOtoIni.cpp \
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
    Frontend/Base/Graphics/GraphicsArea.cpp \
    Frontend/Base/Graphics/GraphicsBaseView.cpp \
    Frontend/Base/Graphics/GraphicsDragger.cpp \
    Frontend/Base/Graphics/GraphicsHandle.cpp \
    Frontend/Base/Graphics/GraphicsLineEdit.cpp \
    Frontend/Base/Graphics/GraphicsLineHandle.cpp \
    Frontend/Base/Graphics/GraphicsLinearView.cpp \
    Frontend/Base/Graphics/GraphicsPlaneHandle.cpp \
    Frontend/Base/Storage/MorePoint.cpp \
    Frontend/Base/Storage/MoreSize.cpp \
    Frontend/Base/Storage/Operation.cpp \
    Frontend/Base/Widgets/BaseDialog.cpp \
    Frontend/Base/Widgets/BaseTab.cpp \
    Frontend/Base/Widgets/MoreWidget.cpp \
    Frontend/Base/Widgets/TransparentContainer.cpp \
    Frontend/Containers/LinearScrollArea.cpp \
    Frontend/Containers/TabWidget.cpp \
    Frontend/Controls/Buttons/IconButton.cpp \
    Frontend/Controls/Buttons/LabelButton.cpp \
    Frontend/Controls/Buttons/SwitchButton.cpp \
    Frontend/Controls/Buttons/SwitchButtons/SwitchButtonGroup.cpp \
    Frontend/Controls/Buttons/SwitchButtons/SwitchButtonUnderline.cpp \
    Frontend/Controls/Buttons/TextButton.cpp \
    Frontend/Controls/Buttons/VectorButton.cpp \
    Frontend/Controls/Group/ComboControl.cpp \
    Frontend/Controls/Group/LineControl.cpp \
    Frontend/Controls/Group/SlideControl.cpp \
    Frontend/Controls/Group/SlideLineControl.cpp \
    Frontend/Controls/Group/TextControl.cpp \
    Frontend/Controls/Inputs/FixedComboBox.cpp \
    Frontend/Controls/Inputs/FixedLineEdit.cpp \
    Frontend/Controls/Inputs/FixedSpinBox.cpp \
    Frontend/Controls/Inputs/FixedTextEdit.cpp \
    Frontend/Controls/Others/TemporaryMenu.cpp \
    Frontend/Dialogs/Extern/BackstageDialog.cpp \
    Frontend/Dialogs/Extern/ExecutePluginDialog.cpp \
    Frontend/Dialogs/Extern/ScriptPluginDialog.cpp \
    Frontend/Dialogs/Extern/TerminalDialog.cpp \
    Frontend/Dialogs/Project/InsertLyricsDialog.cpp \
    Frontend/Dialogs/Project/NotePropertiesDialog.cpp \
    Frontend/Dialogs/Project/ProjectSettingsDialog.cpp \
    Frontend/Dialogs/Template/InputDialog.cpp \
    Frontend/Dialogs/Template/SelectsDialog.cpp \
    Frontend/Process/BaseWork.cpp \
    Frontend/Process/ConcatenateWork.cpp \
    Frontend/Process/RealtimeRenderer.cpp \
    Frontend/Process/ResampleWork.cpp \
    Frontend/Singletons/CentralTabWidget.cpp \
    Frontend/Singletons/CentralTabWidgets/CentralTabWidget_Base.cpp \
    Frontend/Singletons/CentralTabWidgets/CentralTabWidget_Features.cpp \
    Frontend/Singletons/ComboSelector.cpp \
    Frontend/Tabs/Central/CentralTab.cpp \
    Frontend/Tabs/Central/CentralTabContent.cpp \
    Frontend/Tabs/Central/LayerGroup.cpp \
    Frontend/Tabs/Keyboard/Contents/KeyModifyDialog.cpp \
    Frontend/Tabs/Keyboard/Contents/KeyTableTab.cpp \
    Frontend/Tabs/Keyboard/Contents/KeyTableTabs/KeyTableTab_ContextMenu.cpp \
    Frontend/Tabs/Keyboard/Contents/KeyTableTabs/KeyTableTab_Core.cpp \
    Frontend/Tabs/Keyboard/Contents/KeyTableTabs/KeyTableTab_Operation.cpp \
    Frontend/Tabs/Keyboard/KeyboardTab.cpp \
    Frontend/Tabs/Keyboard/KeyboardTab_Core.cpp \
    Frontend/Tabs/Keyboard/KeyboardTab_Edit.cpp \
    Frontend/Tabs/Keyboard/KeyboardTab_Init.cpp \
    Frontend/Tabs/Keyboard/Operations/KeyOperation.cpp \
    Frontend/Tabs/Setting/SettingTab.cpp \
    Frontend/Tabs/Setting/SettingTabs/Operations/SettingOperation.cpp \
    Frontend/Tabs/Setting/SettingTabs/SettingTab_Edit.cpp \
    Frontend/Tabs/Tuning/Base/BaseForm.cpp \
    Frontend/Tabs/Tuning/Base/BaseForms/FormSplitter.cpp \
    Frontend/Tabs/Tuning/Base/BaseForms/FormTitleBar.cpp \
    Frontend/Tabs/Tuning/Base/BaseInterface.cpp \
    Frontend/Tabs/Tuning/Controllers/DraggerHandler.cpp \
    Frontend/Tabs/Tuning/Controllers/EnvelopeHandler.cpp \
    Frontend/Tabs/Tuning/Controllers/EnvelopeHandlers/EnvelopeHandler_Assist.cpp \
    Frontend/Tabs/Tuning/Controllers/EnvelopeHandlers/EnvelopeHandler_Paint.cpp \
    Frontend/Tabs/Tuning/Controllers/EnvelopeHandlers/EnvelopeHandler_States.cpp \
    Frontend/Tabs/Tuning/Controllers/EnvelopeHandlers/EnvelopeHandler_Variate.cpp \
    Frontend/Tabs/Tuning/Controllers/Mode2Handler.cpp \
    Frontend/Tabs/Tuning/Controllers/Mode2Handlers/Mode2Handler_Assist.cpp \
    Frontend/Tabs/Tuning/Controllers/Mode2Handlers/Mode2Handler_Paint.cpp \
    Frontend/Tabs/Tuning/Controllers/Mode2Handlers/Mode2Handler_States.cpp \
    Frontend/Tabs/Tuning/Controllers/Mode2Handlers/Mode2Handler_Variate.cpp \
    Frontend/Tabs/Tuning/Controllers/ScopeHandler.cpp \
    Frontend/Tabs/Tuning/Controllers/ScopeHandlers/ScopeHandler_Assist.cpp \
    Frontend/Tabs/Tuning/Controllers/ScopeHandlers/ScopeHandler_Core.cpp \
    Frontend/Tabs/Tuning/Controllers/ScopeHandlers/ScopeHandler_Move.cpp \
    Frontend/Tabs/Tuning/Controllers/ScopeHandlers/ScopeHandler_Properties.cpp \
    Frontend/Tabs/Tuning/Controllers/ScopeHandlers/ScopeHandler_States.cpp \
    Frontend/Tabs/Tuning/Controllers/ScopeHandlers/ScopeHandler_Variate.cpp \
    Frontend/Tabs/Tuning/Controllers/VibratoHandlers/VibratoHandler_Adjust.cpp \
    Frontend/Tabs/Tuning/Controllers/VibratoHandlers/VibratoHandler_Coordinate.cpp \
    Frontend/Tabs/Tuning/Controllers/VibratoHandlers/VibratoHandler_Core.cpp \
    Frontend/Tabs/Tuning/Controllers/VibratoHandlers/VibratoHandler_Paint.cpp \
    Frontend/Tabs/Tuning/Controllers/VibratoHandlers/VibratoHandler_Properties.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesArea.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Actions.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Adjust.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Assist.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Associate.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Bar.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Const.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Core.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Drag.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Draw.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Events.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Find.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Lyric.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Modify.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Move.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Operation.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Paste.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Play.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Properties.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Render.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Select.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Sprite.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_States.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Update.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/NotesAreas/NotesArea_Variate.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/PianoArea.cpp \
    Frontend/Tabs/Tuning/Editor/Areas/SectionsArea.cpp \
    Frontend/Tabs/Tuning/Editor/EditorForm.cpp \
    Frontend/Tabs/Tuning/Editor/EditorForms/EditorForm_ContextMenu.cpp \
    Frontend/Tabs/Tuning/Editor/EditorInterface.cpp \
    Frontend/Tabs/Tuning/Editor/EditorInterfaces/EditorInterface_Call.cpp \
    Frontend/Tabs/Tuning/Editor/EditorInterfaces/EditorInterface_Link.cpp \
    Frontend/Tabs/Tuning/Editor/Elements/PianoKey.cpp \
    Frontend/Tabs/Tuning/Editor/Modules/EnvButtonGroup.cpp \
    Frontend/Tabs/Tuning/Editor/Modules/FindReplaceDialog.cpp \
    Frontend/Tabs/Tuning/Editor/Modules/PlayButtonGroup.cpp \
    Frontend/Tabs/Tuning/Editor/Modules/SpriteAdjustDialog.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsBar.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifter.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifters/GraphicsLifter_Assist.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifters/GraphicsLifter_Events.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifters/GraphicsLifter_Link.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifters/GraphicsLifter_Paint.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifters/GraphicsLifter_Properties.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifters/GraphicsLifter_States.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifters/GraphicsLifter_Variate.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsLines.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNote.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_Adjust.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_Assist.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_ContextMenu.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_Events.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_Link.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_Paint.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_Properties.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_States.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_Update.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsNotes/GraphicsNote_Values.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsPlayHead.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsPoint.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsPoints/GraphicsPoint_Events.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsPoints/GraphicsPoint_Link.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsPoints/GraphicsPoint_Properties.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsRubber.cpp \
    Frontend/Tabs/Tuning/Graphics/GraphicsSprite.cpp \
    Frontend/Tabs/Tuning/Graphics/VibratoHandles/VibratoBaseHandle.cpp \
    Frontend/Tabs/Tuning/Graphics/VibratoHandles/VibratoLineHandle.cpp \
    Frontend/Tabs/Tuning/Graphics/VibratoHandles/VibratoPlaneHandle.cpp \
    Frontend/Tabs/Tuning/Graphics/VolumePoint.cpp \
    Frontend/Tabs/Tuning/Handlers/PluginHandler.cpp \
    Frontend/Tabs/Tuning/Handlers/ProjectInfoHandler.cpp \
    Frontend/Tabs/Tuning/Operations/NoteOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/ImplicitOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/LengthOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/LyricsOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/MoveOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/PointsOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/PropsOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/ScatterOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/SequenceOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Notes/TempoOperation.cpp \
    Frontend/Tabs/Tuning/Operations/ProjectOperation.cpp \
    Frontend/Tabs/Tuning/Operations/TrackOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Tracks/TrackModifyOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Tracks/TrackSeqOperation.cpp \
    Frontend/Tabs/Tuning/Operations/Tracks/TrackSwitchOperation.cpp \
    Frontend/Tabs/Tuning/Operations/TuneOperation.cpp \
    Frontend/Tabs/Tuning/Params/Areas/LiftersArea.cpp \
    Frontend/Tabs/Tuning/Params/Areas/LiftersAreas/LiftersArea_Adjust.cpp \
    Frontend/Tabs/Tuning/Params/Areas/LiftersAreas/LiftersArea_Move.cpp \
    Frontend/Tabs/Tuning/Params/Areas/LiftersAreas/LiftersArea_Properties.cpp \
    Frontend/Tabs/Tuning/Params/Areas/LiftersAreas/LiftersArea_States.cpp \
    Frontend/Tabs/Tuning/Params/Areas/ParamsDialArea.cpp \
    Frontend/Tabs/Tuning/Params/ParamsForm.cpp \
    Frontend/Tabs/Tuning/Params/ParamsInterface.cpp \
    Frontend/Tabs/Tuning/Scrolls/LiftersScrollArea.cpp \
    Frontend/Tabs/Tuning/Scrolls/NoneScrollArea.cpp \
    Frontend/Tabs/Tuning/Scrolls/NotesScrollArea.cpp \
    Frontend/Tabs/Tuning/Scrolls/NotesScrollAreas/NotesScrollArea_Colors.cpp \
    Frontend/Tabs/Tuning/Tracks/Areas/BlocksArea.cpp \
    Frontend/Tabs/Tuning/Tracks/Areas/HeadsArea.cpp \
    Frontend/Tabs/Tuning/Tracks/Areas/HeadsAreas/HeadsArea_Operations.cpp \
    Frontend/Tabs/Tuning/Tracks/Areas/HeadsAreas/HeadsArea_Reload.cpp \
    Frontend/Tabs/Tuning/Tracks/Elements/SectionsLine.cpp \
    Frontend/Tabs/Tuning/Tracks/Elements/TrackContent.cpp \
    Frontend/Tabs/Tuning/Tracks/Elements/TrackHead.cpp \
    Frontend/Tabs/Tuning/Tracks/TrackInterfaces/TracksInterface_ContextMenu.cpp \
    Frontend/Tabs/Tuning/Tracks/TrackInterfaces/TracksInterface_Default.cpp \
    Frontend/Tabs/Tuning/Tracks/TracksForm.cpp \
    Frontend/Tabs/Tuning/Tracks/TracksInterface.cpp \
    Frontend/Tabs/Tuning/TuningGroup.cpp \
    Frontend/Tabs/Tuning/TuningTab.cpp \
    Frontend/Tabs/Tuning/TuningTab_Core.cpp \
    Frontend/Tabs/Tuning/TuningTab_Edit.cpp \
    Frontend/Tabs/Tuning/TuningTab_Init.cpp \
    Frontend/Tabs/Tuning/TuningTab_Modify.cpp \
    Frontend/Tabs/Tuning/TuningTab_NoteProperty.cpp \
    Frontend/Tabs/Tuning/TuningTab_Oto.cpp \
    Frontend/Tabs/Tuning/TuningTab_Play.cpp \
    Frontend/Tabs/Tuning/TuningTab_Plugin.cpp \
    Frontend/Tabs/Tuning/TuningTab_ProjectSettings.cpp \
    Frontend/Tabs/Tuning/TuningTab_Properties.cpp \
    Frontend/Tabs/Tuning/TuningTab_Realtime.cpp \
    Frontend/Tabs/Tuning/TuningTab_Render.cpp \
    Frontend/Tabs/Tuning/TuningTab_Unchange.cpp \
    Frontend/Tabs/Voice/VoiceBankTab.cpp \
    Frontend/Tabs/Voice/Areas/OtoDataArea.cpp \
    Frontend/Tabs/Voice/Areas/OtoDataAreas/OtoDataArea_Change.cpp \
    Frontend/Tabs/Voice/Areas/OtoDataAreas/OtoDataArea_Operation.cpp \
    Frontend/Tabs/Voice/Areas/OtoInfoArea.cpp \
    Frontend/Tabs/Voice/Areas/OtoInfoAreas/OtoInfoArea_Avatar.cpp \
    Frontend/Tabs/Voice/Areas/OtoInfoAreas/OtoInfoArea_Change.cpp \
    Frontend/Tabs/Voice/Areas/OtoInfoAreas/OtoInfoArea_Operation.cpp \
    Frontend/Tabs/Voice/Areas/OtoPlayerArea.cpp \
    Frontend/Tabs/Voice/Areas/OtoVisionArea.cpp \
    Frontend/Tabs/Voice/Areas/OtoVisionAreas/OtoVisionArea_Cursor.cpp \
    Frontend/Tabs/Voice/Areas/OtoVisionAreas/OtoVisionArea_Handle.cpp \
    Frontend/Tabs/Voice/Areas/OtoVisionAreas/OtoVisionArea_Operation.cpp \
    Frontend/Tabs/Voice/Areas/OtoVisionAreas/OtoVisionArea_Scroll.cpp \
    Frontend/Tabs/Voice/Areas/VoiceBankArea.cpp \
    Frontend/Tabs/Voice/Areas/WaveformArea.cpp \
    Frontend/Tabs/Voice/Graphics/GraphicsOtoHandle.cpp \
    Frontend/Tabs/Voice/Modules/ImageLabel.cpp \
    Frontend/Tabs/Voice/Modules/PlayerLabel.cpp \
    Frontend/Tabs/Voice/Operations/NonOtoOperation.cpp \
    Frontend/Tabs/Voice/Operations/NonOtoOperations/InfoTextOperation.cpp \
    Frontend/Tabs/Voice/Operations/NonOtoOperations/PrefixOperation.cpp \
    Frontend/Tabs/Voice/Operations/OtoOperation.cpp \
    Frontend/Tabs/Voice/Operations/OtoOperations/OtoChangeOperation.cpp \
    Frontend/Tabs/Voice/Operations/OtoOperations/OtoMoveOperation.cpp \
    Frontend/Tabs/Voice/Operations/OtoOperations/OtoVariateOperation.cpp \
    Frontend/Tabs/Voice/Operations/VoiceOperation.cpp \
    Frontend/Tabs/Voice/Scrolls/ImageScrollArea.cpp \
    Frontend/Tabs/Voice/Scrolls/WaveformScrollArea.cpp \
    Frontend/Tabs/Voice/VoiceBankGroup.cpp \
    Frontend/Tabs/Voice/VoiceBankTab_Core.cpp \
    Frontend/Tabs/Voice/VoiceBankTab_Edit.cpp \
    Frontend/Tabs/Voice/VoiceBankTab_Extern.cpp \
    Frontend/Tabs/Voice/VoiceBankTab_Init.cpp \
    Frontend/Tabs/Voice/VoiceBankTab_Oto.cpp \
    Frontend/Tabs/Voice/VoiceBankTab_Play.cpp \
    Frontend/Tabs/Voice/VoiceBankTab_Unchange.cpp \
    Frontend/Tabs/Voice/VoiceTabs/ImageTab.cpp \
    Frontend/Tabs/Voice/VoiceTabs/OtoTableTab.cpp \
    Frontend/Tabs/Voice/VoiceTabs/OtoTableTabs/OtoTableTab_ContextMenu.cpp \
    Frontend/Tabs/Voice/VoiceTabs/OtoTableTabs/OtoTableTab_Properties.cpp \
    Frontend/Tabs/Voice/VoiceTabs/OtoTableTabs/OtoTableTab_Row.cpp \
    Frontend/Tabs/Voice/VoiceTabs/OtoTableTabs/OtoTableTab_Set.cpp \
    Frontend/Tabs/Voice/VoiceTabs/PrefixMapTab.cpp \
    Frontend/Tabs/Voice/VoiceTabs/TextBoxTab.cpp \
    Frontend/Tabs/Welcome/FileListWidget.cpp \
    Frontend/Tabs/Welcome/FileListWidgetItem.cpp \
    Frontend/Tabs/Welcome/WelcomeTab.cpp \
    Frontend/Tabs/Welcome/WelcomeTabContent.cpp \
    Frontend/Utils/FileParser.cpp \
    Frontend/Utils/FilePasers/FileParser_SynthV.cpp \
    Frontend/Utils/FilePasers/FileParser_Vocaloid.cpp \
    Frontend/Utils/FilePasers/FilePasers_Midi.cpp \
    Global/Macros.cpp \
    Global/Methods.cpp \
    Global/QS/Constants.cpp \
    Global/QS/Primary.cpp \
    Global/QS/SystemApis.cpp \
    Global/QUtils.cpp \
    Global/QS/Types.cpp \
    Global/QS/Variables.cpp \
    Global/UTAU/Common/QControlPoint.cpp \
    Global/UTAU/Common/QCorrectGenon.cpp \
    Global/UTAU/Common/QGenonSettings.cpp \
    Global/UTAU/Common/QLinkNote.cpp \
    Global/UTAU/Common/QUtauStd.cpp \
    Global/UTAU/DataSets/SectionNotes.cpp \
    Global/UTAU/DataSets/SectionSettings.cpp \
    Global/UTAU/DataSets/SectionVersion.cpp \
    Global/UTAU/QUtauBasic.cpp \
    Global/UTAU/QUtauRender.cpp \
    Global/UTAU/QUtauSections.cpp \
    Global/UTAU/QUtauStrCore.cpp \
    Global/UTAU/QUtauStrExtern.cpp \
    Global/UTAU/Render/Args/RenderArgs.cpp \
    Global/UTAU/Render/Args/ResamplerArgs.cpp \
    Global/UTAU/Render/Args/WavtoolArgs.cpp \
    Global/UTAU/Render/QBatchRenderer.cpp \
    Global/UTAU/Render/QBatchRenderer_Unix.cpp \
    Global/UTAU/Render/QBatchRenderer_Win.cpp \
    Global/UTAU/Render/Utils/UtaPitchCurves.cpp \
    Global/UTAU/Render/Utils/UtaTranslator.cpp \
    Global/Utils/ItemList.cpp \
    Main/main.cpp \
    Main/resources.cpp \
    Main/total.cpp \
    MainWindow/Actions/common.cpp \
    MainWindow/Actions/editor.cpp \
    MainWindow/Actions/preview.cpp \
    MainWindow/Actions/shortcuts.cpp \
    MainWindow/Actions/tempmenu.cpp \
    MainWindow/Actions/tuning.cpp \
    MainWindow/Actions/voice.cpp \
    MainWindow/Events/drag.cpp \
    MainWindow/Events/window.cpp \
    MainWindow/Exec/exec.cpp \
    MainWindow/Menu/initmenu.cpp \
    MainWindow/Menu/reload.cpp \
    MainWindow/Modules/filedata.cpp \
    MainWindow/Modules/managers.cpp \
    MainWindow/Modules/memory.cpp \
    MainWindow/States/recent.cpp \
    MainWindow/States/status.cpp \
    MainWindow/Tabs/change.cpp \
    MainWindow/Tabs/find.cpp \
    MainWindow/Tabs/handlers.cpp \
    MainWindow/Tabs/inittabs.cpp \
    MainWindow/Tabs/untitle.cpp \
    MainWindow/mainwindow.cpp

HEADERS += \
    Application/Managers/ClientManager.h \
    Application/Managers/ColorTheme.h \
    Application/Managers/DataManager.h \
    Application/Managers/MemoryManager.h \
    Application/Managers/PluginManager.h \
    Application/Managers/VoiceManager.h \
    Application/MiniSystem/MiniSystem.h \
    Application/MiniSystem/MiniSystemNotifier.h \
    Application/MiniSystem/MiniSystemWatcher.h \
    Application/MiniSystem/PathTree.h \
    Application/MiniSystem/efsw/efsw.hpp \
    Application/application.h \
    Backend/Base/BaseDirInfo.h \
    Backend/Base/BaseFile.h \
    Backend/Common/QOtoSample.h \
    Backend/Common/QOtoSampleList.h \
    Backend/Documents/DirInfos/PluginInfo.h \
    Backend/Documents/DirInfos/VoiceInfo.h \
    Backend/Documents/Files/ConfigFile.h \
    Backend/Documents/Files/SequenceTextFile.h \
    Backend/Documents/Files/SettingIniFile.h \
    Backend/Documents/Files/ShortcutsFile.h \
    Backend/Documents/Import/QFrequencyFile.h \
    Backend/Documents/Import/QMidiFile.h \
    Backend/Documents/Import/QPresampFile.h \
    Backend/Documents/Import/QSynthVFile.h \
    Backend/Documents/Import/QVocaloidFile.h \
    Backend/Documents/Import/QWaveInfo.h \
    Backend/Structures/Find/FindOption.h \
    Backend/Structures/Transfer/NoteProperties.h \
    Backend/Structures/Transfer/NoteReadonlys.h \
    Backend/Structures/Transfer/PluginTempData.h \
    Backend/Utils/QDumpFile.h \
    Backend/Utils/QFileSet.h \
    Backend/Utils/QSettingFile.h \
    Backend/Utils/QWavetool.h \
    Backend/VoiceBank/QOtoIni.h \
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
    Frontend/Base/Graphics/GraphicsArea.h \
    Frontend/Base/Graphics/GraphicsBaseView.h \
    Frontend/Base/Graphics/GraphicsDragger.h \
    Frontend/Base/Graphics/GraphicsHandle.h \
    Frontend/Base/Graphics/GraphicsLineEdit.h \
    Frontend/Base/Graphics/GraphicsLineHandle.h \
    Frontend/Base/Graphics/GraphicsLinearView.h \
    Frontend/Base/Graphics/GraphicsPlaneHandle.h \
    Frontend/Base/Storage/MorePoint.h \
    Frontend/Base/Storage/MoreSize.h \
    Frontend/Base/Storage/Operation.h \
    Frontend/Base/Widgets/BaseDialog.h \
    Frontend/Base/Widgets/BaseTab.h \
    Frontend/Base/Widgets/MoreWidget.h \
    Frontend/Base/Widgets/TransparentContainer.h \
    Frontend/Containers/LinearScrollArea.h \
    Frontend/Containers/TabWidget.h \
    Frontend/Controls/Buttons/IconButton.h \
    Frontend/Controls/Buttons/LabelButton.h \
    Frontend/Controls/Buttons/SwitchButton.h \
    Frontend/Controls/Buttons/SwitchButtons/SwitchButtonGroup.h \
    Frontend/Controls/Buttons/SwitchButtons/SwitchButtonUnderline.h \
    Frontend/Controls/Buttons/TextButton.h \
    Frontend/Controls/Buttons/VectorButton.h \
    Frontend/Controls/Group/ComboControl.h \
    Frontend/Controls/Group/LineControl.h \
    Frontend/Controls/Group/SlideControl.h \
    Frontend/Controls/Group/SlideLineControl.h \
    Frontend/Controls/Group/TextControl.h \
    Frontend/Controls/Inputs/FixedComboBox.h \
    Frontend/Controls/Inputs/FixedLineEdit.h \
    Frontend/Controls/Inputs/FixedSpinBox.h \
    Frontend/Controls/Inputs/FixedTextEdit.h \
    Frontend/Controls/Others/TemporaryMenu.h \
    Frontend/Dialogs/Extern/BackstageDialog.h \
    Frontend/Dialogs/Extern/ExecutePluginDialog.h \
    Frontend/Dialogs/Extern/ScriptPluginDialog.h \
    Frontend/Dialogs/Extern/TerminalDialog.h \
    Frontend/Dialogs/Project/InsertLyricsDialog.h \
    Frontend/Dialogs/Project/NotePropertiesDialog.h \
    Frontend/Dialogs/Project/ProjectSettingsDialog.h \
    Frontend/Dialogs/Template/InputDialog.h \
    Frontend/Dialogs/Template/SelectsDialog.h \
    Frontend/Process/BaseWork.h \
    Frontend/Process/ConcatenateWork.h \
    Frontend/Process/RealtimeRenderer.h \
    Frontend/Process/ResampleWork.h \
    Frontend/QSActions.h \
    Frontend/QSTabs.h \
    Frontend/Singletons/CentralTabWidget.h \
    Frontend/Singletons/ComboSelector.h \
    Frontend/Tabs/Central/CentralTab.h \
    Frontend/Tabs/Central/CentralTabContent.h \
    Frontend/Tabs/Central/LayerGroup.h \
    Frontend/Tabs/Keyboard/Contents/KeyModifyDialog.h \
    Frontend/Tabs/Keyboard/Contents/KeyTableTab.h \
    Frontend/Tabs/Keyboard/KeyboardTab.h \
    Frontend/Tabs/Keyboard/Operations/KeyOperation.h \
    Frontend/Tabs/Setting/SettingTab.h \
    Frontend/Tabs/Setting/SettingTabs/Operations/SettingOperation.h \
    Frontend/Tabs/Tuning/Base/BaseForm.h \
    Frontend/Tabs/Tuning/Base/BaseForms/FormSplitter.h \
    Frontend/Tabs/Tuning/Base/BaseForms/FormTitleBar.h \
    Frontend/Tabs/Tuning/Base/BaseInterface.h \
    Frontend/Tabs/Tuning/Controllers/DraggerHandler.h \
    Frontend/Tabs/Tuning/Controllers/EnvelopeHandler.h \
    Frontend/Tabs/Tuning/Controllers/Mode2Handler.h \
    Frontend/Tabs/Tuning/Controllers/ScopeHandler.h \
    Frontend/Tabs/Tuning/Editor/Areas/NotesArea.h \
    Frontend/Tabs/Tuning/Editor/Areas/PianoArea.h \
    Frontend/Tabs/Tuning/Editor/Areas/SectionsArea.h \
    Frontend/Tabs/Tuning/Editor/EditorForm.h \
    Frontend/Tabs/Tuning/Editor/EditorInterface.h \
    Frontend/Tabs/Tuning/Editor/Elements/PianoKey.h \
    Frontend/Tabs/Tuning/Editor/Modules/EnvButtonGroup.h \
    Frontend/Tabs/Tuning/Editor/Modules/FindReplaceDialog.h \
    Frontend/Tabs/Tuning/Editor/Modules/PlayButtonGroup.h \
    Frontend/Tabs/Tuning/Editor/Modules/SpriteAdjustDialog.h \
    Frontend/Tabs/Tuning/Graphics/GraphicsBar.h \
    Frontend/Tabs/Tuning/Graphics/GraphicsLifter.h \
    Frontend/Tabs/Tuning/Graphics/GraphicsLines.h \
    Frontend/Tabs/Tuning/Graphics/GraphicsNote.h \
    Frontend/Tabs/Tuning/Graphics/GraphicsPlayHead.h \
    Frontend/Tabs/Tuning/Graphics/GraphicsPoint.h \
    Frontend/Tabs/Tuning/Graphics/GraphicsRubber.h \
    Frontend/Tabs/Tuning/Graphics/GraphicsSprite.h \
    Frontend/Tabs/Tuning/Graphics/VibratoHandles/VibratoBaseHandle.h \
    Frontend/Tabs/Tuning/Graphics/VibratoHandles/VibratoLineHandle.h \
    Frontend/Tabs/Tuning/Graphics/VibratoHandles/VibratoPlaneHandle.h \
    Frontend/Tabs/Tuning/Graphics/VolumePoint.h \
    Frontend/Tabs/Tuning/Handlers/PluginHandler.h \
    Frontend/Tabs/Tuning/Handlers/ProjectInfoHandler.h \
    Frontend/Tabs/Tuning/Operations/NoteOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/ImplicitOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/LengthOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/LyricsOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/MoveOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/PointsOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/PropsOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/ScatterOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/SequenceOperation.h \
    Frontend/Tabs/Tuning/Operations/Notes/TempoOperation.h \
    Frontend/Tabs/Tuning/Operations/ProjectOperation.h \
    Frontend/Tabs/Tuning/Operations/TrackOperation.h \
    Frontend/Tabs/Tuning/Operations/Tracks/TrackModifyOperation.h \
    Frontend/Tabs/Tuning/Operations/Tracks/TrackSeqOperation.h \
    Frontend/Tabs/Tuning/Operations/Tracks/TrackSwitchOperation.h \
    Frontend/Tabs/Tuning/Operations/TuneOperation.h \
    Frontend/Tabs/Tuning/Params/Areas/LiftersArea.h \
    Frontend/Tabs/Tuning/Params/Areas/ParamsDialArea.h \
    Frontend/Tabs/Tuning/Params/ParamsForm.h \
    Frontend/Tabs/Tuning/Params/ParamsInterface.h \
    Frontend/Tabs/Tuning/Scrolls/LiftersScrollArea.h \
    Frontend/Tabs/Tuning/Scrolls/NoneScrollArea.h \
    Frontend/Tabs/Tuning/Scrolls/NotesScrollArea.h \
    Frontend/Tabs/Tuning/Tracks/Areas/BlocksArea.h \
    Frontend/Tabs/Tuning/Tracks/Areas/HeadsArea.h \
    Frontend/Tabs/Tuning/Tracks/Elements/SectionsLine.h \
    Frontend/Tabs/Tuning/Tracks/Elements/TrackContent.h \
    Frontend/Tabs/Tuning/Tracks/Elements/TrackHead.h \
    Frontend/Tabs/Tuning/Tracks/TracksForm.h \
    Frontend/Tabs/Tuning/Tracks/TracksInterface.h \
    Frontend/Tabs/Tuning/TuningGroup.h \
    Frontend/Tabs/Tuning/TuningTab.h \
    Frontend/Tabs/Voice/VoiceBankTab.h \
    Frontend/Tabs/Voice/Areas/OtoDataArea.h \
    Frontend/Tabs/Voice/Areas/OtoInfoArea.h \
    Frontend/Tabs/Voice/Areas/OtoPlayerArea.h \
    Frontend/Tabs/Voice/Areas/OtoVisionArea.h \
    Frontend/Tabs/Voice/Areas/VoiceBankArea.h \
    Frontend/Tabs/Voice/Areas/WaveformArea.h \
    Frontend/Tabs/Voice/Graphics/GraphicsOtoHandle.h \
    Frontend/Tabs/Voice/Modules/ImageLabel.h \
    Frontend/Tabs/Voice/Modules/PlayerLabel.h \
    Frontend/Tabs/Voice/Operations/NonOtoOperation.h \
    Frontend/Tabs/Voice/Operations/NonOtoOperations/InfoTextOperation.h \
    Frontend/Tabs/Voice/Operations/NonOtoOperations/PrefixOperation.h \
    Frontend/Tabs/Voice/Operations/OtoOperation.h \
    Frontend/Tabs/Voice/Operations/OtoOperations/OtoChangeOperation.h \
    Frontend/Tabs/Voice/Operations/OtoOperations/OtoMoveOperation.h \
    Frontend/Tabs/Voice/Operations/OtoOperations/OtoVariateOperation.h \
    Frontend/Tabs/Voice/Operations/VoiceOperation.h \
    Frontend/Tabs/Voice/Scrolls/ImageScrollArea.h \
    Frontend/Tabs/Voice/Scrolls/WaveformScrollArea.h \
    Frontend/Tabs/Voice/VoiceBankGroup.h \
    Frontend/Tabs/Voice/VoiceTabs/ImageTab.h \
    Frontend/Tabs/Voice/VoiceTabs/OtoTableTab.h \
    Frontend/Tabs/Voice/VoiceTabs/PrefixMapTab.h \
    Frontend/Tabs/Voice/VoiceTabs/TextBoxTab.h \
    Frontend/Tabs/Welcome/FileListWidget.h \
    Frontend/Tabs/Welcome/FileListWidgetItem.h \
    Frontend/Tabs/Welcome/WelcomeTab.h \
    Frontend/Tabs/Welcome/WelcomeTabContent.h \
    Frontend/Utils/FileParser.h \
    Global/Macros.h \
    Global/Methods.h \
    Global/QS/Constants.h \
    Global/QS/Primary.h \
    Global/QS/SystemApis.h \
    Global/QUtils.h \
    Global/QS/Types.h \
    Global/QS/Variables.h \
    Global/UTAU/Common/QControlPoint.h \
    Global/UTAU/Common/QCorrectGenon.h \
    Global/UTAU/Common/QGenonSettings.h \
    Global/UTAU/Common/QLinkNote.h \
    Global/UTAU/Common/QUtauStd.h \
    Global/UTAU/DataSets/SectionNotes.h \
    Global/UTAU/DataSets/SectionSettings.h \
    Global/UTAU/DataSets/SectionVersion.h \
    Global/UTAU/QUtauBasic.h \
    Global/UTAU/QUtauRender.h \
    Global/UTAU/QUtauSections.h \
    Global/UTAU/QUtauStrCore.h \
    Global/UTAU/QUtauStrExtern.h \
    Global/UTAU/Render/Args/RenderArgs.h \
    Global/UTAU/Render/Args/ResamplerArgs.h \
    Global/UTAU/Render/Args/WavtoolArgs.h \
    Global/UTAU/Render/QBatchRenderer.h \
    Global/UTAU/Render/Utils/UtaPitchCurves.h \
    Global/UTAU/Render/Utils/UtaTranslator.h \
    Global/UTAU/Strings/UtaCharText.h \
    Global/UTAU/Strings/UtaFilenames.h \
    Global/UTAU/Strings/UtaPluginText.h \
    Global/UTAU/Strings/UtaProjectText.h \
    Global/UTAU/Strings/UtaSettingIni.h \
    Global/Utils/ItemList.h \
    Main/resources.h \
    Main/total.h \
    MainWindow/mainwindow.h

win32 {
    RC_FILE += \
    Resources/platforms/win/res.rc

    win32-msvc {
        CONFIG(release, debug|release) {
            contains(DEFINES, WIN64) {
                LIBS += -L$$PWD/Libraries/windows/msvc2019_64/ -lefsw-static-release
                PRE_TARGETDEPS += $$PWD/Libraries/windows/msvc2019_64/efsw-static-release.lib
            } else {
                LIBS += -L$$PWD/Libraries/windows/msvc2019/ -lefsw-static-release
                PRE_TARGETDEPS += $$PWD/Libraries/windows/msvc2019/efsw-static-release.lib
            }
        }
        else:CONFIG(debug, debug|release) {
            contains(DEFINES, WIN64) {
                LIBS += -L$$PWD/Libraries/windows/msvc2019_64/ -lefsw-static-debug
                PRE_TARGETDEPS += $$PWD/Libraries/windows/msvc2019_64/efsw-static-debug.lib
            } else {
                LIBS += -L$$PWD/Libraries/windows/msvc2019/ -lefsw-static-debug
                PRE_TARGETDEPS += $$PWD/Libraries/windows/msvc2019/efsw-static-debug.lib
            }
        }
    }
    win32-g++ {
        CONFIG(release, debug|release) {
            !contains(QT_ARCH, i386) {
                LIBS += -L$$PWD/Libraries/windows/mingw81_64/ -lefsw-static-release
                PRE_TARGETDEPS += $$PWD/Libraries/windows/mingw81_64/efsw-static-release.lib
            } else {
                LIBS += -L$$PWD/Libraries/windows/mingw81/ -lefsw-static-release
                PRE_TARGETDEPS += $$PWD/Libraries/windows/mingw81/efsw-static-release.lib
            }
        }
        else:CONFIG(debug, debug|release) {
            !contains(QT_ARCH, i386) {
                LIBS += -L$$PWD/Libraries/windows/mingw81_64/ -lefsw-static-debug
                PRE_TARGETDEPS += $$PWD/Libraries/windows/mingw81_64/efsw-static-debug.lib
            } else {
                LIBS += -L$$PWD/Libraries/windows/mingw81/ -lefsw-static-debug
                PRE_TARGETDEPS += $$PWD/Libraries/windows/mingw81/efsw-static-debug.lib
            }
        }
    }
}
else:macx {
    ICON = Resources/platforms/mac/qsynth2.icns
    CONFIG(release, debug|release) {
        LIBS += -L$$PWD/Libraries/macosx/clang64/ -lefsw-static-release
        PRE_TARGETDEPS += $$PWD/Libraries/macosx/clang64/libefsw-static-release.a
    }
    else:CONFIG(debug, debug|release) {
        LIBS += -L$$PWD/Libraries/macosx/clang64/ -lefsw-static-debug
        PRE_TARGETDEPS += $$PWD/Libraries/macosx/clang64/libefsw-static-debug.a
    }
}
else:unix {
    CONFIG(release, debug|release) {
        LIBS += -L$$PWD/Libraries/linux/x86_64/ -lefsw-static-release
        PRE_TARGETDEPS += $$PWD/Libraries/linux/x86_64/libefsw-static-release.a
    }
    else:CONFIG(debug, debug|release) {
        LIBS += -L$$PWD/Libraries/linux/x86_64/ -lefsw-static-debug
        PRE_TARGETDEPS += $$PWD/Libraries/linux/x86_64/libefsw-static-debug.a
    }
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/res.qrc

INCLUDEPATH += \
    Global \
    Global/QS \
    Global/UTAU \
    Backend \
    Backend/Base \
    Backend/Common \
    Backend/Structures \
    Backend/Utils \
    Backend/Documents/DirInfos \
    Backend/Documents/Files \
    Backend/Documents/Import \
    Frontend \
    Frontend/Base \
    Frontend/Base/Widgets \
    Frontend/Base/Storage \
    Frontend/Common \
    Frontend/Singletons \
    Frontend/Tabs \
    Main \
    MainWindow \
    Application \

TRANSLATIONS += \
    Resources/translations/qsynthesis_cn.ts

DISTFILES += \
    MainWindow/.DS_Store
