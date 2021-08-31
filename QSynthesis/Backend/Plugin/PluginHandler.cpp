#include "PluginHandler.h"
#include "Note/QNoteEnvelope.h"
#include "Note/QNoteMode2.h"
#include "QUtauConstants.h"
#include "QUtauStrings.h"
#include "QUtauUtils.h"
#include "Strings/UtaProjectText.h"

#include "Dialogs/ExecutePluginDialog.h"
#include "Dialogs/ScriptPluginDialog.h"

using namespace UtaProjectText;

PluginHandler::PluginHandler(PluginTempData &data, const PluginInfo &plugin,
                             const QString &workingDir, QWidget *parent)
    : QObject(parent), plugin(plugin), data(data) {
    stateCode = 0;

    // Check dir
    if (!isDirExist(workingDir)) {
        qDebug() << "Working directory doesn't exist.";

        stateCode = -1;
        return;
    }

    QString time = QDateTime::currentDateTime().toString("sszzz");

    // Open fie
    tmpPath = workingDir + Slash + "tmp" + time + ".tmp";
    writeFile();
}

PluginHandler::~PluginHandler() {
}

int PluginHandler::exec() {
    if (stateCode == -1) {
        return stateCode;
    }

    // get exe
    QString exePath, pluginWorkingDir;
    QFileInfo file(plugin.exePath());
    if (!file.isFile()) {
        qDebug() << "Plugin doesn't exist.";

        stateCode = -1;
        return stateCode;
    }

    exePath = file.absoluteFilePath();
    pluginWorkingDir = file.absolutePath();

    QFileSystemWatcher watcher;
    bool fileChanged = false;
    watcher.addPath(tmpPath);

    connect(&watcher, &QFileSystemWatcher::fileChanged, this, [&fileChanged]() mutable {
        qDebug() << "File changed.";
        fileChanged = true;
    });

    // open dialog
    if (plugin.useShell()) {
        ScriptPluginDialog *dlg = new ScriptPluginDialog(tmpPath, exePath, pluginWorkingDir,
                                                         qobject_cast<QWidget *>(parent()));
        stateCode = dlg->exec();

        dlg->deleteLater();
    } else {
        ExecutePluginDialog *dlg = new ExecutePluginDialog(tmpPath, exePath, pluginWorkingDir,
                                                           qobject_cast<QWidget *>(parent()));
        stateCode = dlg->exec();

        dlg->deleteLater();
    }

    if (stateCode != 1) {
        qDebug() << "Plugin is canceled.";
        return stateCode;
    }

    if (!fileChanged) {
        qDebug() << "Temp file is not changed.";
        return 0;
    }

    readFile();

    return stateCode;
}

bool PluginHandler::writeFile() {
    QFile tmpFile(tmpPath);
    if (!tmpFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot create temp file.";

        stateCode = -1;
        return false;
    }

    QTextStream out(&tmpFile);
    if (!plugin.charset().isEmpty()) {
        out.setCodec(plugin.charset().toLatin1());
    }

    // Version
    writeSectionVersion(out);

    // Setting
    writeSectionSettings(out);

    if (!data.notes.isEmpty()) {
        // Prev
        if (data.hasPrev) {
            writeSectionNote(-1, data.notes.front(), data.readonlys.front(), out);
        }

        // Body
        int num = data.start;
        for (int i = data.normalBegin(); i < data.normalEnd(); ++i) {
            writeSectionNote(num, data.notes[i], data.readonlys[i], out);
            ++num;
        }

        // Next
        if (data.hasNext) {
            writeSectionNote(-2, data.notes.back(), data.readonlys.back(), out);
        }
    }

    tmpFile.close();
    return true;
}

bool PluginHandler::readFile() {
    // open file
    QFile tmpFile(tmpPath);

    if (!tmpFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Temp file has been deleted by the plugin.";

        stateCode = -1;
        return stateCode;
    }

    QTextStream in(&tmpFile);
    if (!plugin.charset().isEmpty()) {
        in.setCodec(plugin.charset().toLatin1());
    }

    // read file
    QStringList section;
    QString line;

    QVector<QLinkNote> preNotes;
    QVector<QVector<QLinkNote>> newNotes;

    int start = data.start - data.normalBegin();
    int end = data.start - data.normalBegin() + data.notes.size();
    int currentIndex = start;

    bool hasSection = false;

    // Initialize
    newNotes.resize(data.notes.size());
    for (int i = 0; i < data.notes.size(); ++i) {
        newNotes[i].append(data.notes[i]);
    }

    try {
        while (!in.atEnd()) {
            line = in.readLine();

            if (line.isEmpty() && !in.atEnd()) {
                continue;
            }

            // Continue to add until meet the start of section or end
            if (!line.startsWith(SECTION_BEGIN_MARK) && !in.atEnd()) {
                section.push_back(line);
                continue;
            }

            // If meet end, append without continue
            if (!line.isEmpty() && in.atEnd()) {
                section.push_back(line);
            }

            // Previous section is not empty
            if (section.size() > 0) {
                QString sectionHead, sectionName;
                sectionHead = section[0];
                // If Section Name is invalid
                if (!parseSectionName(sectionHead, sectionName)) {
                    section.clear();
                    continue;
                }

                // If Section Name is a number
                bool isNum = 0;
                int num = sectionName.toInt(&isNum);

                if (isNum) {
                    if (num >= end) {
                        currentIndex = end - 1;
                    } else if (num > currentIndex) {
                        currentIndex = num;
                    }
                    // Parse Note
                    QLinkNote note = data.notes[currentIndex - start];
                    if (parseSectionNote(section, note)) {
                        newNotes[currentIndex - start] = {note}; // Replace
                        hasSection = true;
                    } else {
                        stateCode = -1;
                    }
                    currentIndex++;
                } else if (sectionName == SECTION_NAME_PREV && data.hasPrev) {
                    // Parse Note
                    QLinkNote note = data.notes.front();
                    if (parseSectionNote(section, note)) {
                        newNotes.front() = {note}; // Replace
                        hasSection = true;
                    } else {
                        stateCode = -1;
                    }
                } else if (sectionName == SECTION_NAME_NEXT && data.hasNext) {
                    // Parse Note
                    QLinkNote note = data.notes.back();
                    if (parseSectionNote(section, note)) {
                        newNotes.back() = {note}; // Replace
                        hasSection = true;
                    } else {
                        stateCode = -1;
                    }
                } else if (sectionName == SECTION_NAME_INSERT) {
                    QLinkNote note;
                    // Parse Note
                    if (parseSectionNote(section, note)) {
                        if (currentIndex - 1 - start < 0) {
                            preNotes.append(note); // Append
                            hasSection = true;
                        } else {
                            newNotes[currentIndex - 1 - start].append(note); // Append
                        }
                    } else {
                        stateCode = -1;
                    }
                } else if (sectionName == SECTION_NAME_DELETE) {
                    if (currentIndex - start < newNotes.size()) {
                        // Delete
                        newNotes[currentIndex - start].clear(); // Clear
                        currentIndex++;
                        hasSection = true;
                    }
                }
            }

            section.clear();
            section.push_back(line);
        }
    } catch (...) {
        qDebug() << "Read file error.";
        stateCode = -1;
    }

    if (!hasSection) {
        qDebug() << "No sections in file.";
        stateCode = -1;
    }

    tmpFile.close();
    tmpFile.remove(); // Normal end

    if (stateCode != 1) {
        return stateCode;
    }

    data.notes.clear();
    data.notes.append(preNotes);
    for (int i = 0; i < newNotes.size(); ++i) {
        data.notes.append(newNotes.at(i));
    }

    return stateCode;
}

bool PluginHandler::parseSectionName(const QString &oName, QString &oResult) {
    if (oName.startsWith(SECTION_BEGIN_MARK) && oName.endsWith(SECTION_END_MARK)) {
        oResult = oName.mid(SECTION_BEGIN_MARK.size(),
                            oName.size() - SECTION_BEGIN_MARK.size() - SECTION_END_MARK.size());
        return true;
    } else {
        return false;
    }
}

bool PluginHandler::parseSectionNote(const QStringList &oSectionList, QLinkNote &oNote) {
    QStringList::size_type i;
    bool isValid = true;

    int eq;
    QString key, value;

    int valueInt;
    double valueDouble;
    bool isInt, isDouble;

    QNoteMode2 mode2;
    QNoteEnvelope envelope;

    mode2.SetCorrectedPortamento(oNote.Mode2Pitch.toVector());
    envelope.setEnvelope(oNote.envelope.toVector());

    for (i = 0; i < oSectionList.size(); ++i) {
        eq = oSectionList[i].indexOf("=");
        if (eq <= 0) {
            continue;
        }

        key = oSectionList[i].left(eq);
        value = oSectionList[i].mid(eq + 1);

        valueInt = value.toInt(&isInt);
        valueDouble = value.toDouble(&isDouble);

        if (key == KEY_NAME_LYRIC) {
            oNote.lyric = value; // Lyric
        } else if (key == KEY_NAME_NOTE_NUM && isInt) {
            oNote.noteNum = valueInt; // Note Num
        } else if (key == KEY_NAME_LENGTH && isInt) {
            oNote.length = valueInt; // Length
        } else if (key == KEY_NAME_FLAGS) {
            oNote.flags = value; // Flags
        } else if (key == KEY_NAME_INTENSITY) {
            if (isDouble) {
                oNote.intensity = valueDouble; // Volume
            } else if (value.isEmpty()) {
                oNote.intensity = NODEF_DOUBLE;
            }
        } else if (key == KEY_NAME_MODULATION || key == KEY_NAME_MODURATION) {
            if (isDouble) {
                oNote.modulation = valueDouble; // Modulation
            } else if (value.isEmpty()) {
                oNote.modulation = NODEF_DOUBLE;
            }
        } else if (key == KEY_NAME_PRE_UTTERANCE) {
            if (isDouble) {
                oNote.preUttr = valueDouble; // PreUtterence
            } else if (value.isEmpty()) {
                oNote.preUttr = NODEF_DOUBLE;
            }
        } else if (key == KEY_NAME_VOICE_OVERLAP) {
            if (isDouble) {
                oNote.overlap = valueDouble; // Voice Overlap
            } else if (value.isEmpty()) {
                oNote.overlap = NODEF_DOUBLE;
            }
        } else if (key == KEY_NAME_VELOCITY) {
            if (isDouble) {
                oNote.velocity = valueDouble; // Consonant Velocity
            } else if (value.isEmpty()) {
                oNote.velocity = NODEF_DOUBLE;
            }
        } else if (key == KEY_NAME_START_POINT) {
            if (isDouble) {
                oNote.stp = valueDouble; // StartPoint
            } else if (value.isEmpty()) {
                oNote.stp = NODEF_DOUBLE;
            }
        } else if (key == KEY_NAME_TEMPO) {
            if (isDouble) {
                oNote.tempo = valueDouble; // Tempo
            }
        } else if (key == KEY_NAME_REGION_START) {
            oNote.region = value; // Start of region
        } else if (key == KEY_NAME_REGION_END) {
            oNote.regionEnd = value; // End of region
        } else if (key == KEY_NAME_PB_START && isDouble) {
            if (isDouble) {
                oNote.pbstart = valueDouble; // Mode1 Start
            } else if (value.isEmpty()) {
                oNote.pbstart = NODEF_DOUBLE;
            }
        } else if (key == KEY_NAME_PBS) {
            mode2.SetPBS(value); // Mode2 Start
        } else if (key == KEY_NAME_PBW) {
            mode2.SetPBW(value); // Mode2 Intervals
        } else if (key == KEY_NAME_PBY) {
            mode2.SetPBY(value); // Mode2 Offsets
        } else if (key == KEY_NAME_PBM) {
            mode2.SetPBM(value); // Mode2 Types
        } else if (key == KEY_NAME_PICHES || key == KEY_NAME_PITCHES ||
                   key == KEY_NAME_PITCH_BEND) {
            if (value.isEmpty()) {
                oNote.pitches.clear();
            } else {
                oNote.pitches = qstring_to_qvector_double(value).toList(); // Mode1 Pitch
            }
        } else if (key == KEY_NAME_VBR) {
            if (value.isEmpty()) {
                oNote.vibrato.clear();
            } else {
                oNote.vibrato = qstring_to_qvector_double(value).toList(); // Mode2 Vibrato
            }
        } else if (key == KEY_NAME_ENVELOPE) {
            envelope.setStrEnvelope(value); // Envelope
        } else if (!key.startsWith('@')) {
            oNote.customData.append(qMakePair(key, value)); // Custom Values
        }
    }
    oNote.Mode2Pitch = mode2.GetCorrectedPortamento().toList(); // Mode2 Pitch
    oNote.envelope = envelope.getEnvelope().toList();

    return isValid;
}

void PluginHandler::writeSectionName(const int &oName, QTextStream &oStream) {
    QString aName = QString::number(oName);
    int nums = aName.size();
    for (int i = 0; i < 4 - nums; ++i) {
        aName.prepend("0");
    }
    writeSectionName(aName, oStream);
}

void PluginHandler::writeSectionName(const QString &oName, QTextStream &oStream) {
    oStream << SECTION_BEGIN_MARK + oName + SECTION_END_MARK << Qt::endl;
}

void PluginHandler::writeSectionNote(int num, const QLinkNote &oNote,
                                     const NoteReadonlys &oReadonly, QTextStream &oStream) {
    if (num == -1) {
        writeSectionName(SECTION_NAME_PREV, oStream);
    } else if (num == -2) {
        writeSectionName(SECTION_NAME_NEXT, oStream);
    } else {
        writeSectionName(num, oStream);
    }

    // 可能不出现的条目
    QString aVibrato = qvector_double_to_qstring(oNote.vibrato.toVector());
    QString aPitchBend = qvector_double_to_qstring(oNote.pitches.toVector());

    // 复杂条目
    QNoteMode2 mode2;
    QNoteEnvelope envelope;

    QString aPBS, aPBW, aPBY, aPBM;
    QString aEnvelope;

    mode2.SetCorrectedPortamento(oNote.Mode2Pitch.toVector());
    mode2.ExportStrings(aPBS, aPBW, aPBY, aPBM);

    envelope.setEnvelope(oNote.envelope.toVector());
    aEnvelope = envelope.strEnvelope();

    // Items always exist
    oStream << KEY_NAME_LENGTH << "=" << oNote.length << Qt::endl;
    oStream << KEY_NAME_LYRIC << "=" << oNote.lyric << Qt::endl;
    oStream << KEY_NAME_NOTE_NUM << "=" << oNote.noteNum << Qt::endl;

    // Items can be omitted
    if (oNote.preUttr != NODEF_DOUBLE) {
        oStream << KEY_NAME_PRE_UTTERANCE << "=" << oNote.preUttr << Qt::endl;
    }
    if (oNote.overlap != NODEF_DOUBLE) {
        oStream << KEY_NAME_VOICE_OVERLAP << "=" << oNote.overlap << Qt::endl;
    }
    if (oNote.velocity != NODEF_DOUBLE) {
        oStream << KEY_NAME_VELOCITY << "=" << QString::number(oNote.velocity) << Qt::endl;
    }
    if (oNote.intensity != NODEF_DOUBLE) {
        oStream << KEY_NAME_INTENSITY << "=" << oNote.intensity << Qt::endl;
    }
    if (oNote.modulation != NODEF_DOUBLE) {
        oStream << KEY_NAME_MODULATION << "=" << oNote.modulation << Qt::endl;
    }
    if (oNote.stp != NODEF_DOUBLE) {
        oStream << KEY_NAME_START_POINT << "=" << oNote.stp << Qt::endl;
    }
    if (!oNote.flags.isEmpty()) {
        oStream << KEY_NAME_FLAGS << "=" << oNote.flags << Qt::endl;
    }

    // Items maybe not exist
    if (!oNote.pitches.isEmpty()) {
        oStream << KEY_NAME_PB_TYPE << "=" << VALUE_PITCH_TYPE << Qt::endl;
        oStream << KEY_NAME_PB_START << "=" << oNote.pbstart << Qt::endl;
        oStream << KEY_NAME_PITCH_BEND << "=" << aPitchBend << Qt::endl;
    }
    if (!oNote.Mode2Pitch.isEmpty()) {
        oStream << KEY_NAME_PBS << "=" << aPBS << Qt::endl;
        oStream << KEY_NAME_PBW << "=" << aPBW << Qt::endl;
        oStream << KEY_NAME_PBY << "=" << aPBY << Qt::endl;
        if (!aPBM.isEmpty()) {
            oStream << KEY_NAME_PBM << "=" << aPBM << Qt::endl;
        }
    }
    if (!oNote.envelope.isEmpty()) {
        oStream << KEY_NAME_ENVELOPE << "=" << aEnvelope << Qt::endl;
    }
    if (!oNote.vibrato.isEmpty()) {
        oStream << KEY_NAME_VBR << "=" << aVibrato << Qt::endl;
    }
    if (oNote.tempo != NODEF_DOUBLE) {
        oStream << KEY_NAME_TEMPO << "=" << oNote.tempo << Qt::endl;
    }
    if (oNote.region != NODEF_STRING) {
        oStream << KEY_NAME_REGION_START << "=" << oNote.region << Qt::endl;
    }
    if (oNote.regionEnd != NODEF_STRING) {
        oStream << KEY_NAME_REGION_END << "=" << oNote.regionEnd << Qt::endl;
    }

    // Custom items
    for (int i = 0; i < oNote.customData.size(); ++i) {
        oStream << oNote.customData[i].first << "=" << oNote.customData[i].second << Qt::endl;
    }

    // Readonly items
    if (oReadonly.preuttr != NODEF_DOUBLE) {
        oStream << KEY_NAME_PRE_UTTERANCE_READONLY << "=" << oReadonly.preuttr << Qt::endl;
    }

    if (oReadonly.overlap != NODEF_DOUBLE) {
        oStream << KEY_NAME_VOICE_OVERLAP_READONLY << "=" << oReadonly.overlap << Qt::endl;
    }

    if (oReadonly.stpoint != NODEF_DOUBLE) {
        oStream << KEY_NAME_START_POINT_READONLY << "=" << oReadonly.stpoint << Qt::endl;
    }

    if (oReadonly.filename != NODEF_STRING && !oReadonly.filename.isEmpty()) {
        oStream << KEY_NAME_FILENAME_READONLY << "=" << oReadonly.filename << Qt::endl;
    }

    if (oReadonly.alias != NODEF_STRING && !oReadonly.alias.isEmpty()) {
        oStream << KEY_NAME_ALIAS_READONLY << "=" << oReadonly.alias << Qt::endl;
    }

    if (oReadonly.cache != NODEF_STRING && !oReadonly.cache.isEmpty()) {
        oStream << KEY_NAME_CACHE_READONLY << "=" << oReadonly.cache << Qt::endl;
    }
}

void PluginHandler::writeSectionSettings(QTextStream &oStream) {
    writeSectionName(SECTION_NAME_SETTING, oStream);

    if (data.project != NODEF_STRING) {
        oStream << KEY_NAME_PROJECT << "=" << QDir::toNativeSeparators(data.project) << Qt::endl;
    }

    oStream << KEY_NAME_TEMPO + "=" << data.sectionSettings.globalTempo << Qt::endl;
    oStream << KEY_NAME_VOICE_DIR << "=" << data.sectionSettings.voiceDirectory << Qt::endl;
    oStream << KEY_NAME_CACHE_DIR << "=" << data.sectionSettings.cacheDirectory << Qt::endl;

    if (data.sectionSettings.isMode2) {
        oStream << KEY_NAME_MODE2 << "=" << VALUE_MODE2_ON << Qt::endl;
    }

    if (!data.sectionSettings.globalFlags.isEmpty()) {
        oStream << KEY_NAME_FLAGS << "=" << data.sectionSettings.globalFlags << Qt::endl;
    }
}

void PluginHandler::writeSectionVersion(QTextStream &oStream) {
    writeSectionName(SECTION_NAME_VERSION, oStream);

    oStream << UST_VERSION_PREFIX << data.sectionVersion.version << Qt::endl;
}
