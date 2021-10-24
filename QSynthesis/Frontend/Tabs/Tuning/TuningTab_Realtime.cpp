#include "Editor/Areas/NotesArea.h"
#include "Tracks/TracksInterface.h"
#include "TuningGroup.h"
#include "TuningTab.h"
#include "Utils/QWavetool.h"

#include <QtConcurrent>

void TuningTab::updateCache(int tick) {
    if (isPlaying()) {
        stop();
    }

    int index = m_ptrs->notesArea->findNoteAtTick(tick);
    if (index >= m_ptrs->notesArea->NotesList.size()) {
        return;
    }
    updateCacheCore(index > 0 ? (index - 1) : 0);
}

bool TuningTab::isRendered(int index) const {
    return renderedWorks.contains(index);
}

bool TuningTab::isNotRendered(int index) const {
    return !renderingWorks.contains(index) && !renderedWorks.contains(index);
}

void TuningTab::removeCacheFrom(int index) {
    QString cacheDirPath = defaultCacheDir();

    QDir dir(cacheDirPath);
    QFileInfoList fileList;
    int max = 0;

    fileList = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot, QDir::Name);
    for (auto it = fileList.begin(); it != fileList.end(); ++it) {
        auto info = *it;
        QString filename = info.fileName();
        QString prefix;

        int i = 0;
        while (i < filename.size() && filename.at(i).isNumber()) {
            prefix.append(filename.at(i));
            i++;
        }

        int num = prefix.toInt();
        if (num > max) {
            max = num;
        }
    }

    for (int i = index; i <= max; ++i) {
        if (!renderingWorks.contains(i)) {
            RemoveFilesWithPrefixNumber(cacheDirPath, i);
        }
    }

    if (!renderingWorks.isEmpty()) {
        QSet<int> newSet;
        for (auto it = renderingWorks.begin(); it != renderingWorks.end(); ++it) {
            int val = *it;
            if (val < index) {
                newSet.insert(val);
            }
        }
        renderingWorks = newSet;
    }
    if (!renderedWorks.isEmpty()) {
        QMap<int, QString> newSet;
        for (auto it = renderedWorks.begin(); it != renderedWorks.end(); ++it) {
            int val = it.key();
            if (val < index) {
                newSet.insert(val, it.value());
            }
        }
        renderedWorks = newSet;
    }
    m_ptrs->notesArea->reloadBar();
}

void TuningTab::removeCacheAt(int index) {
    QString cacheDirPath = defaultCacheDir();

    if (!renderingWorks.contains(index)) {
        RemoveFilesWithPrefixNumber(cacheDirPath, index);
    } else {
        renderingWorks.remove(index);
    }
    renderedWorks.remove(index);
    m_ptrs->notesArea->reloadBar();
}

void TuningTab::removeCacheWithin(int x, int y) {
    QString cacheDirPath = defaultCacheDir();
    for (int i = x; i <= y; ++i) {
        if (!renderingWorks.contains(i)) {
            RemoveFilesWithPrefixNumber(cacheDirPath, i);
        } else {
            renderingWorks.remove(i);
        }
        renderedWorks.remove(i);
    }
    m_ptrs->notesArea->reloadBar();
}

void TuningTab::clearCache() {
    renderingWorks.clear();
    renderedWorks.clear();
    m_ptrs->notesArea->reloadBar();
}

void TuningTab::initAudio() {
    int tick = m_ptrs->notesArea->playToTick();
    int index = m_ptrs->notesArea->findNoteAtTick(tick);

    auto SNotesList = m_ptrs->notesArea->NotesList;
    int notesCount = SNotesList.size();
    if (index >= notesCount) {
        return;
    }

    double time = m_ptrs->notesArea->convertTickToTime(tick);
    if (time < 0) {
        return;
    }
    m_startTime = time;
    m_startIndex = index;
    m_processedIndex = index;

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setSampleSize(16);
    format.setChannelCount(1);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);

    //    auto infos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    //    for (const QAudioDeviceInfo &info : infos) {
    //        qDebug() << info.deviceName() << info.isFormatSupported(format);
    //    }
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qDebug() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    m_audio = new QAudioOutput(format, this);
    connect(m_audio, &QAudioOutput::stateChanged, this, &TuningTab::handleAudioStateChanged);
    m_audioBuf = m_audio->start();

    handleAudioTimeout(); // Run Once
}

void TuningTab::quitAudio() {
    audioTimer->stop();

    delete m_audio;
    m_audio = nullptr;
    m_audioBuf = nullptr;

    m_audioData.clear();

    m_startTime = 0;
    m_startIndex = -1;
    m_processedIndex = -1;

    m_startBuffer = 0;

    m_ptrs->notesArea->stopPlaying();
}

void TuningTab::updateCacheCore(int index, int length) {
    QString cacheDirPath = defaultCacheDir();
    if (!isDirExist(cacheDirPath)) {
        CreateDir(cacheDirPath);
    }

    int cnt = 0;
    int notesCount = m_ptrs->notesArea->NotesList.size();
    int total = (length < 0) ? renderer->threadsCount() : length;

    QList<int> prior;
    QList<ResampleWork *> works;

    int i = index;
    while (cnt < total && i < notesCount) {
        if (!renderingWorks.contains(i) && !renderedWorks.contains(i)) {
            renderingWorks.insert(i);

            RenderArgs arg = m_ptrs->notesArea->renderArgsAt(i);
            fixRenderArgs(arg);

            ResampleWork *work = new ResampleWork();
            work->setWorkingDir(m_workingDir);
            work->setResampler(m_ptrs->tracksContent->defaultResampler());
            work->setArgs(arg.resamplerArgs);

            works.append(work);
            prior.append(i);
        }
        i++;
        cnt++;
    }

    renderer->setPriorWorks(prior);
    renderer->addWorks(works);
}

void TuningTab::updateBufferCore(int toIndex) {
    auto SNotesList = m_ptrs->notesArea->NotesList;
    while (toIndex >= m_processedIndex) {
        int index = m_processedIndex;
        if (!renderedWorks.contains(index)) {
            break;
        }
        RenderArgs arg = m_ptrs->notesArea->renderArgsAt(index);
        fixRenderArgs(arg);

        QByteArray data;
        QWavetool wavtool;
        wavtool.setArgs(arg.wavtoolArgs);
        wavtool.load();
        data = wavtool.processedData();

        if (index == m_startIndex) {
            GraphicsNote *p = SNotesList.at(index);
            double time = p->time();
            double pre = p->correctGenon().PreUtterance;

            int frontCut = wavtool.sampleRate() * (pre + m_startTime - time) / 1000;
            int frontCutBytes = frontCut * wavtool.blockAlign();

            QByteArray emp;
            emp.resize(int(44100 * 5) * 2);
            emp.fill(0);

            m_audioData.append(emp);
            m_audioData.append(data);
            m_startBuffer = emp.size() + frontCutBytes;
        } else {
            int frontCut = wavtool.sampleRate() * arg.wavtoolArgs.voiceOverlap() / 1000;
            int block = wavtool.blockAlign();
            int frontCutBytes = frontCut * block;
            if (frontCutBytes >= 0) {
                QByteArray mix = data.left(frontCutBytes);
                data.remove(0, frontCutBytes);
                if (m_audioData.size() < mix.size()) {
                    mix = mix.right(m_audioData.size());
                }
                QByteArray org = m_audioData.right(mix.size());
                m_audioData.chop(mix.size());
                for (int i = 0; i < frontCut; ++i) {
                    short val1 = *(short *) org.mid(i * block, block).data();
                    short val2 = *(short *) mix.mid(i * block, block).data();
                    short val3 = val1 + val2;
                    org.replace(i * block, block, QByteArray((char *) &val3, 2));
                }
                m_audioData.append(org);
                m_audioData.append(data);
            } else {
                QByteArray mute;
                mute.resize(-frontCutBytes);
                mute.fill(0);
                m_audioData.append(mute);
                m_audioData.append(data);
            }
        }
        m_processedIndex++;
    }
}

void TuningTab::handleWorkFinished(int seq, const QString &filename) {
    if (!QDir(defaultCacheDir()).exists(filename)) {
        qDebug() << "Render failed for" << filename;
        // return;
    }
    if (renderingWorks.contains(seq)) {
        renderingWorks.remove(seq);
        renderedWorks.insert(seq, filename);
        m_ptrs->notesArea->reloadBar();
    }
}

void TuningTab::initRenderer() {
    renderer = new RealtimeRenderer(this);
    connect(renderer, &RealtimeRenderer::oneSuccess, this, &TuningTab::handleWorkFinished);

    audioTimer = new QTimer(this);
    connect(audioTimer, &QTimer::timeout, this, &TuningTab::handleAudioTimeout);

    m_audio = nullptr;
    m_audioBuf = nullptr;

    m_startTime = -1;
    m_startIndex = -1;
    m_processedIndex = -1;

    m_startBuffer = 0;
}

void TuningTab::handleAudioTimeout() {
    audioTimer->stop();

    int indexNeed = qMin(m_ptrs->notesArea->findNoteAtTime(position() + 5000),
                         m_ptrs->notesArea->NotesList.size() - 1);
    if (indexNeed >= m_processedIndex) {
        updateCacheCore(m_processedIndex, indexNeed - m_processedIndex + 1);
    }

    updateBufferCore(indexNeed);

    if (!m_audioData.isEmpty() && m_startBuffer < m_audioData.size()) {
        int readSize = m_audio->periodSize();
        int chunks = m_audio->bytesFree() / readSize;
        while (chunks) {
            QByteArray samples;

            if (m_startBuffer > 0) {
                samples = m_audioData.mid(m_startBuffer, readSize);
                m_audioData.remove(0, samples.size() + m_startBuffer);
                m_startBuffer = 0;
            } else {
                samples = m_audioData.mid(0, readSize);
                m_audioData.remove(0, samples.size());
            }

            if (!samples.isEmpty()) {
                m_audioBuf->write(samples);
            }
            if (samples.size() != readSize) {
                break;
            }
            chunks--;
        }
    }
    m_ptrs->notesArea->advancePlaying(position());

    audioTimer->start(20);
}

void TuningTab::handleAudioStateChanged(QAudio::State state) {
    if (state == QAudio::IdleState && m_processedIndex >= m_ptrs->notesArea->NotesList.size()) {
        stop();
    }
}
