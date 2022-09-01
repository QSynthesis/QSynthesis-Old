#include "Editor/Areas/NotesArea.h"
#include "Editor/EditorForm.h"
#include "Handlers/ProjectInfoHandler.h"
#include "Tracks/TracksInterface.h"
#include "TuningGroup.h"
#include "TuningTab.h"
#include "mainwindow.h"

#include "Dialogs/Extern/BackstageDialog.h"
#include "Dialogs/Extern/TerminalDialog.h"
#include "Render/Utils/UtaTranslator.h"

using namespace Utau;

bool TuningTab::renderSelection() {
    // Step 1: Call Notes-Area
    // Step 2: Fetch all parameters from Note of GUI Note
    // Step 3: If in Mode2, compute pitch curves string by reference of time values
    // Step 4: Set parameters to WavtoolArgs and ResamplerArgs class
    // Step 5: If in command line, write the parameters to batch file
    // Step 6: Execute batch file

    QList<RenderArgs> args = m_ptrs->notesArea->prepareRender();

    if (args.isEmpty()) {
        return false;
    }

    QString tempBatPath = m_workingDir + Slash + FILE_NAME_TEMP_BATCH;
    QString helperBatPath = m_workingDir + Slash + FILE_NAME_HELPER_BATCH;
    QString cacheDirPath = defaultCacheDir();
    QString tempAudioName = FILE_NAME_TEMP_AUDIO;

    QString voiceDirPath = m_ptrs->tracksContent->defaultVoiceDir();
    QString wavtoolPath = projectInfo->wavtool();
    QString resamplerPath = m_ptrs->tracksContent->defaultResampler();
    QString globalFlags = m_ptrs->tracksContent->defaultFlags();

#ifdef Q_OS_WINDOWS
    // Generate temp.bat
    QFile tempFile(tempBatPath);

    if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(qRoot, ErrorTitle, tr("Unable to create batch file!"));
        return 0;
    }

    QTextStream fs(&tempFile);

    // Initial part of temp.bat
    fs << "@set loadmodule=" << Qt::endl;
    fs << "@set tempo=" << args.at(0).resamplerArgs.tempo() << Qt::endl;
    fs << "@set samples=" << 44100 << Qt::endl;
    fs << "@set oto=" << QDir::toNativeSeparators(voiceDirPath) << Qt::endl;
    fs << "@set tool=" << QDir::toNativeSeparators(wavtoolPath) << Qt::endl;
    fs << "@set resamp=" << QDir::toNativeSeparators(resamplerPath) << Qt::endl;
    fs << "@set output=" << tempAudioName << Qt::endl;
    fs << "@set helper="
       << "temp_helper.bat" << Qt::endl;
    fs << "@set cachedir=" << QDir::toNativeSeparators(cacheDirPath) << Qt::endl;
    fs << "@set flag="
       << "\"" << globalFlags << "\"" << Qt::endl;
    fs << "@set env="
       << "0 5 35 0 100 100 0" << Qt::endl;
    fs << "@set stp=" << 0 << Qt::endl;

    fs << Qt::endl;
    fs << "@del \"%output%\" 2>nul" << Qt::endl;
    fs << "@mkdir \"%cachedir%\" 2>nul" << Qt::endl;
    fs << Qt::endl;
    fs << Qt::endl;

    int i;
    int count = args.size();

    for (i = 0; i < count; ++i) {
        fixRenderArgs(args[i]);

        ResamplerArgs res = args.at(i).resamplerArgs;
        WavtoolArgs wav = args.at(i).wavtoolArgs;

        QGenonSettings aGenon = res.genonSettings();
        QCorrectGenon aCorrect = res.correctGenon();

        if (wav.isRest()) {
            fs << "@\"%tool%\" \"%output%\" \"%oto%\\R.wav\" 0";
            fs << " " << wav.outDuration(); // Static Duration
            fs << " 0 0";
            fs << Qt::endl;
        } else {
            fs << "@echo " << UtaTranslator::LoadingBar(i + 1, count) << Qt::endl;

            fs << "@set params=" << res.paramsArguments().join(" ") << Qt::endl;
            fs << "@set flag="
               << "\"" << res.flags() << "\"" << Qt::endl;
            fs << "@set env=" << wav.envArguments().join(" ") << Qt::endl;

            fs << "@set stp=" << wav.startPoint() << Qt::endl;
            fs << "@set vel=" << res.velocity() << Qt::endl;
            fs << "@set temp="
               << "\"%cachedir%\\" << PathFindFileName(res.outFile()) << "\"" << Qt::endl;

            // Transmit parameters
            fs << "@call"
               << " "
               << "\"%helper%\"";
            fs << " "
               << "\"%oto%\\"
               << QDir::toNativeSeparators(PathFindFileName(res.inFile(), voiceDirPath))
               << "\""; // Original file name

            fs << " " << res.toneName();        // Tone Name
            fs << " " << wav.outDuration();     // Static Duration
            fs << " " << aCorrect.PreUtterance; // PreUtterance (May not used)
            fs << " " << aGenon.mOffset;        // Offset (Left Blue Area)
            fs << " " << res.realLength();
            fs << " " << aGenon.mConstant; // Consonant (Constant Area)
            fs << " " << aGenon.mBlank;    // Blank (Right Blue Area)
            fs << " " << res.sequence();   // Sequence Number

            fs << Qt::endl;
        }
        fs << Qt::endl;
    }

    fs << Qt::endl;

    fs << "@if not exist \"%output%.whd\" goto E" << Qt::endl;
    fs << "@if not exist \"%output%.dat\" goto E" << Qt::endl;
    fs << "copy /Y \"%output%.whd\" /B + \"%output%.dat\" /B \"%output%\"" << Qt::endl;
    fs << "del \"%output%.whd\"" << Qt::endl;
    fs << "del \"%output%.dat\"" << Qt::endl;
    fs << ":E" << Qt::endl;

    tempFile.close();

    // Generate temp_helper.bat
    QFile helperFile(helperBatPath);

    if (!helperFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(qRoot, ErrorTitle, tr("Unable to create batch file!"));
        return 0;
    }

    fs.setDevice(&helperFile);

    fs << "@if exist %temp% goto A" << Qt::endl;
    fs << "@if exist \"%cachedir%\\%9_*.wav\" del \"%cachedir%\\%9_*.wav\"" << Qt::endl;
    fs << "@\"%resamp%\" %1 %temp% %2 %vel% %flag% %5 %6 %7 %8 %params%" << Qt::endl;
    fs << ":A" << Qt::endl;
    fs << "@\"%tool%\" \"%output%\" %temp% %stp% %3 %env%" << Qt::endl;

    helperFile.close();

#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    // Generate temp.sh
    QFile tempFile(tempBatPath);

    if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, ErrorTitle, tr("Unable to create batch file!"));
        return 0;
    }

    QTextStream fs(&tempFile);

    // Initial part of temp.sh
    fs << "#!/bin/sh" << Qt::endl;
    fs << Qt::endl;

    fs << "export loadmodule=" << Qt::endl;
    fs << "export tempo=" << args.at(0).resamplerArgs.tempo() << Qt::endl;
    fs << "export samples=" << 44100 << Qt::endl;
    fs << "export oto="
       << "\'" << voiceDirPath << "\'" << Qt::endl;
    fs << "export tool="
       << "\'" << wavtoolPath << "\'" << Qt::endl;
    fs << "export resamp="
       << "\'" << resamplerPath << "\'" << Qt::endl;
    fs << "export output="
       << "\'" << tempAudioName << "\'" << Qt::endl;
    fs << "export helper="
       << "\'"
       << "./temp_helper.sh"
       << "\'" << Qt::endl;
    fs << "export cachedir="
       << "\'" << cacheDirPath << "\'" << Qt::endl;
    fs << "export flag="
       << "\'" << globalFlags << "\'" << Qt::endl;
    fs << "export env="
       << "\'0 5 35 0 100 100 0\'" << Qt::endl;
    fs << "export stp=" << 0 << Qt::endl;

    fs << Qt::endl;
    fs << "rm -rf \"${output}\"" << Qt::endl;
    fs << "mkdir \"${cachedir}\"" << Qt::endl;
    fs << Qt::endl;
    fs << Qt::endl;

    int i;

    int count = args.size();

    for (i = 0; i < count; ++i) {
        fixRenderArgs(args[i]);

        ResamplerArgs res = args.at(i).resamplerArgs;
        WavtoolArgs wav = args.at(i).wavtoolArgs;

        QGenonSettings aGenon = res.genonSettings();
        QCorrectGenon aCorrect = res.correctGenon();

        if (wav.isRest()) {
            fs << "\"${tool}\" \"${output}\" \"${oto}/R.wav\" 0";
            fs << " " << wav.outDuration(); // Static Duration
            fs << " 0 0";
            fs << Qt::endl;
        } else {
            fs << "echo "
               << "\'" << UtaTranslator::loadingBar(i + 1, count) << "\'" << Qt::endl;

            fs << "export params="
               << "\'" << res.paramsArguments().join(" ") << "\'" << Qt::endl;
            fs << "export flag="
               << "\'" << res.flags() << "\'" << Qt::endl;
            fs << "export env="
               << "\'" << wav.envArguments().join(" ") << "\'" << Qt::endl;

            fs << "export stp=" << wav.startPoint() << Qt::endl;
            fs << "export vel=" << res.velocity() << Qt::endl;
            fs << "export temp="
               << "\"${cachedir}/" << PathFindFileName(res.outFile()) << "\"" << Qt::endl;

            // Transmit parameters
            fs << "\"${helper}\"";
            fs << " "
               << "\"${oto}/" << PathFindFileName(res.inFile(), voiceDirPath)
               << "\""; // Original file name

            fs << " " << res.toneName();        // Tone Name
            fs << " " << wav.outDuration();     // Static Duration
            fs << " " << aCorrect.PreUtterance; // PreUtterance (May not used)
            fs << " " << aGenon.mOffset;        // Offset (Left Blue Area)
            fs << " " << res.realLength();
            fs << " " << aGenon.mConstant; // Consonant (Constant Area)
            fs << " " << aGenon.mBlank;    // Blank (Right Blue Area)
            fs << " " << res.sequence();   // Sequence Number

            fs << Qt::endl;
        }
        fs << Qt::endl;
    }

    fs << Qt::endl;

    fs << "if [ -f \"${output}.whd\" ] && [ -f \"${output}.dat\" ]; then" << Qt::endl;
    fs << "\t"
       << "cat \"${output}.whd\" \"${output}.dat\" > \"${output}\"" << Qt::endl;
    fs << "\t"
       << "rm -f \"${output}.whd\"" << Qt::endl;
    fs << "\t"
       << "rm -f \"${output}.dat\"" << Qt::endl;
    fs << "fi" << Qt::endl;

    tempFile.close();

    // Generate temp_helper.sh
    QFile helperFile(helperBatPath);

    if (!helperFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, ErrorTitle, tr("Unable to create batch file!"));
        return 0;
    }

    fs.setDevice(&helperFile);

    fs << "#!/bin/sh" << Qt::endl;
    fs << Qt::endl;

    fs << "if [ ! -f \"${temp}\" ]; then" << Qt::endl;
    fs << "\t"
       << "rm -rf \"${cachedir}/$9_*.wav\"" << Qt::endl;
    fs << "\t"
       << "\"${resamp}\" \"$1\" \"${temp}\" $2 ${vel} \"${flag}\" $5 $6 $7 $8 ${params}"
       << Qt::endl;
    fs << "fi" << Qt::endl;
    fs << "\"${tool}\" \"${output}\" \"${temp}\" ${stp} $3 ${env}" << Qt::endl;

    helperFile.close();

    // Grant executable permissions
    QProcess p;
    p.start("chmod a+x " + tempBatPath);
    p.waitForFinished();
    p.start("chmod a+x " + helperBatPath);
    p.waitForFinished();
#endif

    return 1;
}

void TuningTab::fixRenderArgs(RenderArgs &args) {
    QString cacheDirPath = defaultCacheDir();
    QString tempAudioName = FILE_NAME_TEMP_AUDIO;

    ResamplerArgs &res = args.resamplerArgs;
    WavtoolArgs &wav = args.wavtoolArgs;

    args.wavtoolPath = projectInfo->wavtool();
    args.resamplerPath = m_ptrs->tracksContent->defaultResampler();

    QString aFlags = res.flags();
    aFlags += m_ptrs->tracksContent->defaultFlags();
    aFlags = UtaTranslator::fixFlags(aFlags);

    res.setFlags(aFlags);          // Add Global Flags
    wav.setOutFile(tempAudioName); // Set Temp Wav

    res.setOutFile(cacheDirPath + Slash + res.outFile());
    wav.setInFile(cacheDirPath + Slash + wav.inFile());
}

bool TuningTab::renderCore() {
    if (!isDirExist(m_ptrs->tracksContent->defaultVoiceDir())) {
        QMessageBox::warning(this, ErrorTitle, tr("Voice database is not available."));
        return 0;
    }
    QFileInfo wavtool(projectInfo->wavtool());
    if (!wavtool.isFile()) {
        QMessageBox::warning(this, ErrorTitle, tr("Wavtool doesn't exist."));
        return 0;
    } else if (!wavtool.isExecutable()) {
        QMessageBox::warning(this, ErrorTitle, tr("Wavtool is not executable."));
        return 0;
    }
    QFileInfo resamp(m_ptrs->tracksContent->defaultResampler());
    if (!resamp.isFile()) {
        QMessageBox::warning(this, ErrorTitle, tr("Resampler doesn't exist."));
        return 0;
    } else if (!resamp.isExecutable()) {
        QMessageBox::warning(this, ErrorTitle, tr("Resampler is not executable."));
        return 0;
    }

    bool batch = renderSelection();

    if (!batch) {
        return 0;
    }

    qDebug() << "[I/O]"
             << "Generate Batch File Success";

    // Close File
    // setMedia(QMediaContent());
    // setPlaying(false);

    // Open Dialog And Wait
    TerminalDialog *dlg = new TerminalDialog(workingDir(), this);
    //    BackstageDialog *dlg = new BackstageDialog(workingDir(), this);
    //    dlg->setThreads(12);
    //    dlg->setArgs(currentRenderArgs);

    int code = dlg->exec();
    dlg->deleteLater();

    if (code == 0) {
        qDebug() << "[Process]"
                 << "Render exited abnormally";
        return 0;
    } else if (code == -1) {
        qDebug() << "[Process]"
                 << "Render exited manually";
        return 0;
    }

    if (!isFileExist(tempAudioFile())) {
        qDebug() << "[I/O]"
                 << "Unable to load wav file";
        return 0;
    }

    return true;
}
