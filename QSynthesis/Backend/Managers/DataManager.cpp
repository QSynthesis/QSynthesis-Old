#include "DataManager.h"
#include "Variables.h"

Q_SINGLETON_DECLARE(DataManager)

QList<QTranslator *> DataManager::Translators{};

DataManager::DataManager(QObject *parent) : QObject(parent) {
}

DataManager::~DataManager() {
}

void DataManager::reloadStrings() {
    ErrorTitle = tr("Error");
    UntitledFileName = tr("Untitled");
    DeletedPrefix = tr("(Deleted)");

#ifdef Q_OS_WINDOWS
    fileManagerName = tr("Explorer");
#elif defined(Q_OS_MAC)
    fileManagerName = tr("Finder");
#else
    fileManagerName = tr("file manager");
#endif

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

bool DataManager::translate(const QString &filename) {
    QTranslator *t = new QTranslator(self);
    if (t->load(filename)) {
        qApp->installTranslator(t);
        Translators.append(t);
        return true;
    }
    delete t;
    return false;
}

void DataManager::eliminate() {
    for (QTranslator *t : Translators) {
        qApp->removeTranslator(t);
        delete t;
    }
    Translators.clear();
}
