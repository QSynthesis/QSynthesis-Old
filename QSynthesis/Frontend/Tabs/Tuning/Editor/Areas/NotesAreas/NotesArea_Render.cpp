#include "../../../Tracks/TracksInterface.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"
#include "Render/RenderUtils/UtaPitchCurves.h"
#include "Render/RenderUtils/UtaTranslator.h"

QList<RenderArgs> NotesArea::getRenderArgsCore(QPoint range) const {
    QList<RenderArgs> args;

    int left = (range.x() < 0 || range.x() > NotesList.size() - 1) ? 0 : range.x();
    int right =
        (range.y() < 0 || range.y() > NotesList.size() - 1) ? (NotesList.size() - 1) : range.y();

    for (int i = left; i <= right; ++i) {
        GraphicsNote *aNote = NotesList.at(i);
        GraphicsNote *aPrevNote = aNote->prev();
        GraphicsNote *aNextNote = aNote->next();

        int aNoteNum = aNote->Note.noteNum;
        int aLength = aNote->Note.length;

        QString aFlags = aNote->Note.flags;
        QString aLyric = aNote->Note.lyric;

        double aTempo = aNote->tempo();

        double aIntensity = aNote->intensity();
        double aModulation = aNote->modulation();
        double aVelocity = aNote->velocity();

        QGenonSettings aGenon = aNote->genonSettings();
        QCorrectGenon aCorrect = aNote->correctGenon();

        double aPreUttr = aCorrect.PreUtterance;
        double aOverlap = aCorrect.VoiceOverlap;
        double aStartPoint = aCorrect.StartPoint;

        QVector<QControlPoint> aPitch;
        QVector<QControlPoint> aEnvelope;
        QVector<double> aVibrato;

        // Compute Mode2 Pitch Bend
        QVector<QControlPoint> aPrevPitch;
        QVector<double> aPrevVibrato;
        QString aPrevLyric = "";

        int aPrevLength = 480;
        int aPrevNoteNum = aNoteNum;

        int aNextLength = 480;
        int aNextNoteNum;

        double aNextPreUttr = 0;
        double aNextOverlap = 0;

        QVector<QControlPoint> aNextPitch;
        QVector<double> aNextVibrato;

        if (aGenon.mFileName.isEmpty()) {
            aGenon.mFileName = m_ptrs->tracksContent->defaultVoiceDir() + Slash + aLyric + ".wav";
        }

        // Previous Note
        if (aPrevNote) {
            aPrevLength = aPrevNote->Note.length;
            aPrevLyric = aPrevNote->Note.lyric;
            aPrevNoteNum = aPrevNote->Note.noteNum;
            aPrevPitch = aPrevNote->Note.Mode2Pitch.toVector(); // Mode2 Pitch Control Points
            aPrevVibrato = aPrevNote->Note.vibrato.toVector();  // Mode2 Vibrato

            if (!aPrevPitch.isEmpty()) {
                GraphicsNote *NoteBeforePrev = aPrevNote->prev();
                if (NoteBeforePrev) {
                    QString tmpLyric = NoteBeforePrev->Note.lyric;
                    int tmpNoteNum = NoteBeforePrev->Note.noteNum;

                    UtaTranslator::getCorrectPBSY(tmpNoteNum, tmpLyric, aPrevNoteNum,
                                                  aPrevPitch.front());
                }
            }
        }

        // Current Note
        {
            aPitch = aNote->Note.Mode2Pitch.toVector();  // Mode2 Mode2 Pitch Control Points
            aEnvelope = aNote->Note.envelope.toVector(); // Envelope
            aVibrato = aNote->Note.vibrato.toVector();   // Mode2 Vibrato

            // Correct the y coordinate of first point
            if (!aPitch.isEmpty()) {
                UtaTranslator::getCorrectPBSY(aPrevNoteNum, aPrevLyric, aNoteNum, aPitch.front());
            }
        }

        // Next Note
        if (aNextNote) {
            QCorrectGenon nextGenon = aNextNote->correctGenon();

            aNextNoteNum = aNextNote->Note.noteNum; // Note Num
            aNextLength = aNextNote->Note.length;   // Length

            aNextPreUttr = nextGenon.PreUtterance; // PreUtterance
            aNextOverlap = nextGenon.VoiceOverlap; // Overlap

            aNextPitch = aNextNote->Note.Mode2Pitch.toVector(); // Mode2 Mode2 Pitch Control Points
            aNextVibrato = aNextNote->Note.vibrato.toVector();  // Mode2 Vibrato

            // Correct the y coordinate of first point
            if (!aNextPitch.isEmpty()) {
                UtaTranslator::getCorrectPBSY(aNoteNum, aLyric, aNextNoteNum, aNextPitch.front());
            }
        }

        if (aPitch.isEmpty()) {
            aPitch = UtaTranslator::defaultPitch(aPrevNoteNum, aPrevLyric, aNoteNum);
        }

        // Convert Mode2 to Mode1
        QVector<int> aPitchValues;
        aPitchValues = UtaPitchCurves::convert_from_vector_point(
            aTempo, aPitch, aVibrato, aPreUttr, aStartPoint, aLength, aNextPitch, aNextVibrato,
            aNextPreUttr, aNextOverlap, aNextLength, aPrevPitch, aPrevVibrato, aPrevLength);

        // Real Length
        double aDuration = (double(aLength) / 480 * 60 / aTempo * 1000); // 由 ticks 换算长度
        double aDurationFix = aPreUttr - aNextPreUttr + aNextOverlap;

        double aRealLength = aDuration + aDurationFix + aStartPoint + 50;
        aRealLength = (aRealLength < aGenon.mConstant) ? aGenon.mConstant : aRealLength;
        aRealLength = int((aRealLength + 25) / 50) * 50;

        // Cache Name
        QString aToneName = tone_number_to_tone_name(aNoteNum);
        QString cacheName = QString::number(i) + "_" + UtaTranslator::compatibleFileName(aLyric) +
                            "_" + aToneName + "_" + QString::number(aLength) + ".wav";

        // Save Values to Class
        ResamplerArgs res;
        WavtoolArgs wav;

        // Resampler Arguments
        res.setGenonSettings(aGenon);     // Genon Settings
        res.setToneName(aToneName);       // Note Num
        res.setOutFile(cacheName);        // Output File
        res.setIntensity(aIntensity);     // Intensity
        res.setModulation(aModulation);   // Modulation
        res.setVelocity(aVelocity);       // Velocity
        res.setFlags(aFlags);             // Flags
        res.setTempo(aTempo);             // Tempo
        res.setPitchCurves(aPitchValues); // Pitch
        res.setRealLength(aRealLength);   // Real Length
        res.setCorrectGenon(aCorrect);    // Useless...

        res.setSequence(i);

        // Wavtool Arguments
        wav.setInFile(cacheName);
        wav.setOutFile(""); // Modify Later
        wav.setStartPoint(aStartPoint);
        wav.setLength(aLength);          // Out Duration Arg 1
        wav.setTempo(aTempo);            // Out Duration Arg 2
        wav.setCorrection(aDurationFix); // Out Duration Arg 3
        wav.setVoiceOverlap(aOverlap);
        wav.setEnvelope(aEnvelope);

        if (aNote->isRest()) {
            wav.setRest(true);
        }

        // Add to list
        args.append(RenderArgs(res, wav));
    }
    return args;
}

QList<RenderArgs> NotesArea::prepareRender() {
    qDragOut.filter(GraphicsDragger::Note);
    if (qDragOut.selectedNotes.isEmpty()) {
        return {};
    }
    m_renderRange = selectContinuously();
    return getRenderArgsCore(m_renderRange);
}

QList<RenderArgs> NotesArea::allRenderArgs() const {
    return getRenderArgsCore(QPoint(-1, -1));
}
