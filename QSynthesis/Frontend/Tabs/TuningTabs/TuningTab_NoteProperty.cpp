#include "../TuningTab.h"
#include "Areas/Editor/NotesArea.h"
#include "Backend/Note/QLinkNote.h"
#include "Dialogs/NotePropertiesDialog.h"
#include "TuningGroup.h"
#include "mainwindow.h"

void TuningTab::showNoteProperty() {
    if (m_ptrs->draggers.selectedNotes.isEmpty()) {
        return;
    }
    if (!isFreeButPlaying()) {
        return;
    }
    forcePausePlaying();

    m_ptrs->draggers.filter(GraphicsDragger::Note);

    QList<NoteProperties> list = m_ptrs->notesArea->selectedProperties();
    NoteProperties np, np2;

    {
        QString firstInt, firstMod, firstPre, firstOve, firstVel, firstStp, firstLen;
        QString firstFlags;

        QString curInt, curMod, curPre, curOve, curVel, curStp, curLen;
        QString curFlags;

        bool intDif, modDif, flagsDif, preDif, oveDif, velDif, stpDif, lenDif;

        const NoteProperties &p = list.front();

        // Leftmost note
        firstLen = p.length;

        firstInt = p.intensity;
        firstMod = p.modulation;

        firstPre = p.preUttr;
        firstOve = p.overlap;

        firstStp = p.startpoint;
        firstVel = p.velocity;

        firstFlags = p.flags;

        intDif = modDif = flagsDif = preDif = oveDif = velDif = stpDif = lenDif = false;

        for (int i = 1; i < list.size(); ++i) {
            const NoteProperties &p = list.at(i);

            // Current note
            curLen = p.length;

            curInt = p.intensity;
            curMod = p.modulation;

            curPre = p.preUttr;
            curOve = p.overlap;

            curStp = p.startpoint;
            curVel = p.velocity;

            curFlags = p.flags;

            if (curInt != firstInt) {
                intDif = true;
            }
            if (curMod != firstMod) {
                modDif = true;
            }
            if (curPre != firstPre) {
                preDif = true;
            }
            if (curOve != firstOve) {
                oveDif = true;
            }
            if (curVel != firstVel) {
                velDif = true;
            }
            if (curStp != firstStp) {
                stpDif = true;
            }
            if (curFlags != firstFlags) {
                flagsDif = true;
            }

            if (curLen != firstLen) {
                lenDif = true;
            }
        }

        np.length = lenDif ? NODEF_STRING : firstLen;

        np.intensity = intDif ? NODEF_STRING : firstInt;
        np.modulation = modDif ? NODEF_STRING : firstMod;

        np.preUttr = preDif ? NODEF_STRING : firstPre;
        np.overlap = oveDif ? NODEF_STRING : firstOve;

        np.velocity = velDif ? NODEF_STRING : firstVel;
        np.startpoint = stpDif ? NODEF_STRING : firstStp;

        np.flags = flagsDif ? NODEF_STRING : firstFlags;

        if (list.size() == 1) {
            np.preUttrOto = p.preUttrOto;
            np.overlapOto = p.overlapOto;
        }
    }

    np2 = np;

    NotePropertiesDialog *dlg = new NotePropertiesDialog(np, list.size(), this);
    int code = -1;

    code = dlg->exec();
    dlg->deleteLater();

    if (code != 1) {
        return;
    }

    // Save
    m_ptrs->notesArea->modifySelectedNotes(np2, np);
}

void TuningTab::resetNoteProperty() {
    if (m_ptrs->draggers.selectedNotes.isEmpty()) {
        return;
    }
    if (!isFreeButPlaying()) {
        return;
    }
    forcePausePlaying();

    m_ptrs->draggers.filter(GraphicsDragger::Note);

    QList<NoteProperties> list = m_ptrs->notesArea->selectedProperties();
    NoteProperties np, np2;

    np = np2 = list.front();

    np.intensity = np.preUttr = np.overlap = np.flags = np.velocity = np.startpoint =
        np.preUttrOto = np.overlapOto = "";

    np.intensity = QString::number(100);
    np.modulation = QString::number(0);

    // Save
    m_ptrs->notesArea->modifySelectedNotes(np2, np);
}
