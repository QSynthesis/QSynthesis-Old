#include "PianoArea.h"
#include "../../Interfaces/EditorInterface.h"
#include "../../Modules/Elements/PianoKey.h"
#include "../../TuningGroup.h"

#include <QStyle>
#include <QTimer>
#include <cmath>

PianoArea::PianoArea(EditorInterface *editor, QWidget *parent) : MoreWidget(parent) {
    m_ptrs = editor->ptrs();
    setAttribute(Qt::WA_StyledBackground);

    int curHeight, totalPos;

    // White Keys
    totalPos = 0;
    for (int i = TONE_OCTAVE_MIN; i <= TONE_OCTAVE_MAX; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (j == 1 || j == 2 || j == 5) {
                curHeight = 4;
            } else {
                curHeight = 3;
            }

            PianoKey *key = new PianoKey(Qs::White, this);
            key->setHeightFactor(curHeight);
            key->setPosFactor(totalPos);

            totalPos += curHeight;
            m_whites.append(key);
        }
    }

    // Black Keys
    totalPos = 2;
    curHeight = 2;
    for (int i = TONE_OCTAVE_MIN; i <= TONE_OCTAVE_MAX; ++i) {
        for (int j = 0; j < 5; ++j) {
            PianoKey *key = new PianoKey(Qs::Black, this);
            key->setHeightFactor(curHeight);
            key->setPosFactor(totalPos);

            if (j == 0 || j == 1 || j == 3) {
                totalPos += 4;
            } else {
                totalPos += 6;
            }
            m_blacks.append(key);
        }
    }

    for (int i = TONE_OCTAVE_MIN; i <= TONE_OCTAVE_MAX; ++i) {
        QLabel *label = new QLabel("C" + QString::number(TONE_OCTAVE_MAX + 1 - i), this);
        label->setProperty("type", "standard");
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
        label->setFont(uiFont());
        label->adjustSize();
        label->setAlignment(Qt::AlignCenter);
        m_labels.append(label);
    }

    lbToneName = new QLabel(this);
    lbToneName->setProperty("type", "realtime");
    lbToneName->setAttribute(Qt::WA_TransparentForMouseEvents);
    lbToneName->setFont(uiFont());
    lbToneName->setAlignment(Qt::AlignCenter);
    curNoteNum = -1;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PianoArea::handleUpdateToneLabel);
    timer->start(10);

    handleUpdateToneLabel();
    installEventFilter(this);
}

PianoArea::~PianoArea() {
}

void PianoArea::adjustHeight() {
    int curHeight = m_ptrs->currentHeight;

    for (int i = 0; i < m_whites.size(); ++i) {
        PianoKey *key = m_whites.at(i);
        key->move(0, key->posFactor() * curHeight / 2);
        key->setFixedSize(width(), key->heightFactor() * curHeight / 2);
    }

    for (int i = 0; i < m_blacks.size(); ++i) {
        PianoKey *key = m_blacks.at(i);
        key->move(0, key->posFactor() * curHeight / 2);
        key->setFixedSize(width() / 2, key->heightFactor() * curHeight / 2);
    }

    for (int i = 0; i < m_labels.size(); ++i) {
        PianoKey *key = m_whites.at(i * 7 + 6);
        QLabel *label = m_labels.at(i);

        label->move(key->x() + key->width() * 3 / 4 - label->width() / 2,
                    key->y() + key->height() * 2 / 3 - label->height() / 2);
    }

    setFixedHeight((TONE_OCTAVE_MAX - TONE_OCTAVE_MIN + 1) * 12 * curHeight);
    handleUpdateToneLabel();
}

void PianoArea::handleUpdateToneLabel() {
    int currentHeight = m_ptrs->currentHeight;

    QPoint thisMouse = mapFromGlobal(QCursor::pos());

    int index = floor(double(thisMouse.y()) / currentHeight);

    int min = TONE_NUMBER_BASE;
    int max = TONE_NUMBER_BASE + (TONE_OCTAVE_MAX - TONE_OCTAVE_MIN + 1) * 12;
    int number = max - 1 - index;

    if (number == curNoteNum) {
        return;
    } else {
        curNoteNum = number;
    }

    if (number < min || number >= max) {
        lbToneName->setVisible(false);
        return;
    } else {
        lbToneName->setVisible(true);
    }

    int toY = index * currentHeight;

    QString name = tone_number_to_tone_name(curNoteNum);
    if (name.contains('#')) {
        lbToneName->setProperty("black", true);
        style()->polish(lbToneName);
    } else {
        lbToneName->setProperty("black", false);
        style()->polish(lbToneName);
    }

    lbToneName->setText(name);
    lbToneName->adjustSize();
    lbToneName->move(10, toY + (currentHeight - lbToneName->height()) / 2);
}

TuningGroup *PianoArea::ptrs() const {
    return m_ptrs;
}

void PianoArea::resizeEvent(QResizeEvent *event) {
    if (event->oldSize().width() != event->size().width()) {
        for (int i = 0; i < m_whites.size(); ++i) {
            m_whites.at(i)->setFixedWidth(width());
        }
        for (int i = 0; i < m_blacks.size(); ++i) {
            m_blacks.at(i)->setFixedWidth(width() / 2);
        }
        for (int i = 0; i < m_labels.size(); ++i) {
            PianoKey *key = m_whites.at(i * 7 + 6);
            QLabel *label = m_labels.at(i);

            label->move(key->x() + key->width() * 3 / 4 - label->width() / 2, label->y());
        }
        handleUpdateToneLabel();
    }
}

bool PianoArea::eventFilter(QObject *obj, QEvent *event) {
    return QWidget::eventFilter(obj, event);
}
