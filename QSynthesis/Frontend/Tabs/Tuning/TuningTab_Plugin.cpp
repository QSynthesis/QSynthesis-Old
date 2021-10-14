#include "Controls/Others/TemporaryMenu.h"
#include "Editor/Areas/NotesArea.h"
#include "Handlers/PluginHandler.h"
#include "Handlers/ProjectInfoHandler.h"
#include "Tracks/TracksInterface.h"
#include "TuningGroup.h"
#include "TuningTab.h"

void TuningTab::selectPlugin() {
}

void TuningTab::handleRunPlugin(const PluginInfo &plugin) {
    PluginTempData ns;
    QFileInfo file(m_filename);
    if (file.isFile()) {
        ns.project = file.absoluteFilePath();
    }
    ns.sectionVersion = SectionVersion();
    ns.sectionSettings = currentSettings();

    m_ptrs->notesArea->preparePlugin(ns, plugin.allNote());

    QPoint orgRegion =
        QPoint(ns.start - ns.normalBegin(), ns.start - ns.normalBegin() + ns.notes.size() - 1);
    PluginHandler *handler = new PluginHandler(ns, plugin, m_workingDir, this);

    int code = handler->exec();
    handler->deleteLater();

    qDebug() << "Plugin ends with exitcode" << code;

    if (code != 1) {
        return;
    }

    m_ptrs->notesArea->receivePlugin(ns, orgRegion);
}
