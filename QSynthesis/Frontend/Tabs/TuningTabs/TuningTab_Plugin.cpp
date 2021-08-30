#include "../TuningTab.h"
#include "Areas/Editor/NotesArea.h"
#include "Interfaces/TracksInterface.h"
#include "ProjectInfoHandler.h"
#include "Templates/TemporaryMenu.h"
#include "TuningGroup.h"
#include "mainwindow.h"

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

    PluginHandler *handler = new PluginHandler(ns, plugin, m_workingDir);

    int code = handler->exec();
    handler->deleteLater();

    qDebug() << "Plugin ends with exitcode" << code;

    if (code != 1) {
        return;
    }

    m_ptrs->notesArea->receivePlugin(ns, orgRegion);
}
