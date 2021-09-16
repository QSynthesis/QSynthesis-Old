#include "mainwindow.h"

QSharedMemory MainWindow::sharedMemory;

void MainWindow::reloadBackendStrings() {
    ErrorTitle = tr("Error");
    UntitledFileName = tr("Untitled");
    DeletedPrefix = tr("(Deleted)");

#if defined(Q_OS_WINDOWS)
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
    toolsFilterString = tr("Executable(*.exe);;All Files(*.*)");
#else
    openFilterString = tr("UTAU Sequence Text(*.ust);;All Files(*)");
    saveFilterString = tr("UTAU Sequence Text(*.ust);;All Files(*)");
    importFilterString =
        tr("Standard MIDI Files(*.mid);;"
           "Synthesizer V Files(*.svp *.s5p);;VOCALOID Files(*.vsqx *.vsq);;All Files(*)");
    appendFilterString =
        tr("Standard MIDI Files(*.mid);;UTAU Sequence Text(*.ust);;"
           "Synthesizer V Files(*.svp *.s5p);;VOCALOID Files(*.vsqx *.vsq);;All Files(*)");
    exportSelectionFilterString =
        tr("Standard MIDI Files(*.mid);;UTAU Sequence Text(*.ust);;"
           "Synthesizer V Files(*.svp);;VOCALOID Files(*.vsqx);;All Files(*)");
    exportTrackFilterString =
        tr("Standard MIDI Files(*.mid);;"
           "Synthesizer V Files(*.svp);;VOCALOID Files(*.vsqx);;All Files(*)");
    exportOtoIniFilterString = tr("Voice Configurations(oto.ini);;All Files(*)");
    imageFilterString = tr("Image Files(*.bmp *.jpg *.jpeg *.png *.gif *.webp);;All Files(*)");

    audioFilterString = tr("Audio Files(*.wav);;All Files(*)");
    toolsFilterString = tr("Executable(*)");
#endif
}
