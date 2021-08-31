#include "mainwindow.h"

SettingIniData MainWindow::settingIni;
ConfigData MainWindow::config;
ShortcutsData MainWindow::shortcuts;

QSharedMemory MainWindow::sharedMemory;

void MainWindow::reloadBackendStrings() {
    ErrorTitle = tr("Error");
    UntitledFileName = tr("Untitled");
    DeletedPrefix = tr("(Deleted)");

    openFilterString = tr("UTAU Sequence Text(*.ust);;All Files(*.*)");
    saveFilterString = tr("UTAU Sequence Text(*.ust);;All Files(*.*)");
    importFilterString =
        tr("Standard MIDI Files(*.mid);;"
           "Synthesizer V Files(*.svp *.s5p);;VOCALOID Files(*.vsqx *.vsq);;All Files(*.*)");
    appendFilterString =
        tr("Standard MIDI Files(*.mid);;UTAU Sequence Text(*.ust);;"
           "Synthesizer V Files(*.svp *.s5p);;VOCALOID Files(*.vsqx *.vsq);;All Files(*.*)");
    exportSelectionFilterString =
        tr("Standard MIDI Files(*.mid);;UTAU Sequence Text(*.ust);;"
           "Synthesizer V Files(*.svp);;VOCALOID Files(*.vsqx);;All Files(*.*)");
    exportTrackFilterString =
        tr("Standard MIDI Files(*.mid);;"
           "Synthesizer V Files(*.svp);;VOCALOID Files(*.vsqx);;All Files(*.*)");
    exportOtoIniFilterString = tr("Voice Configurations(oto.ini);;All Files(*.*)");
    imageFilterString = tr("Image Files(*.bmp *.jpg *.jpeg *.png *.gif *.webp);;All Files(*.*)");

    audioFilterString = tr("Audio Files(*.wav);;All Files(*.*)");

#if defined(_WIN32)
    toolsFilterString = tr("Executable(*.exe);;All Files(*.*)");
#elif defined(linux)
    toolsFilterString = tr("Executable Files(*.*)");
#else
    toolsFilterString = tr("Executable Files()");
#endif
}
