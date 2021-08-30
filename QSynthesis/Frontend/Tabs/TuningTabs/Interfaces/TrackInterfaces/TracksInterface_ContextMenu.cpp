#include "../TracksInterface.h"
#include "../../Forms/TracksForm.h"
#include "../../TuningGroup.h"

void TracksInterface::handleMenuBtnClicked() {
    QAction *configAction = new QAction(tr("Project Settings..."), m_menu);
    QAction *charsetAction = new QAction(tr("Charset..."), m_menu);

    connect(configAction, &QAction::triggered, this, &TracksInterface::handleConfigTriggered);
    connect(configAction, &QAction::triggered, this, &TracksInterface::handleCharsetTriggered);

    m_menu->addAction(configAction);
    m_menu->addAction(charsetAction);

    m_menu->exec(QCursor::pos());
    m_menu->clear();
}

void TracksInterface::handleConfigTriggered() {
    m_ptrs->tab->showProjectSettings();
}

void TracksInterface::handleCharsetTriggered() {
    m_ptrs->tab->showProjectCharset();
}
