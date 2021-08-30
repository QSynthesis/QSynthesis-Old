#include "Mode2Handler.h"

const QList<QControlPoint> Mode2Handler::defaultPortamento = {QControlPoint(-15, 0),
                                                                QControlPoint(15, 0)};
const QList<double> Mode2Handler::defaultVibrato = {65, 180, 35, 20, 20, 0, 0, 0};

Mode2Handler::Mode2Handler() {
    init();
}

Mode2Handler::Mode2Handler(GraphicsNote *note, NotesArea *editor) : ScopeHandler(note, editor) {
    init();
}

Mode2Handler::~Mode2Handler() {
}

void Mode2Handler::init() {
    m_type = Qs::Mode2;

    m_mode1SolidLineEnabledColor = Qt::red;
    m_mode2SolidLineEnabledColor = Qt::red;

    m_mode1SolidLineDisabledColor = QColor(0xFF, 0x80, 0x80, 192);
    m_mode2SolidLineDisabledColor = QColor(0xFF, 0x80, 0x80, 192);

    m_mode1DashLineEnabledColor = QColor(0xFF, 0, 0, 192);
    m_mode2DashLineEnabledColor = QColor(0xFF, 0, 0, 192);

    m_mode1DashLineDisabledColor = QColor(0xFF, 0x80, 0x80, 192);
    m_mode2DashLineDisabledColor = QColor(0xFF, 0x80, 0x80, 192);

    m_mode2InvalidLineEnabledColor = QColor(0xFF, 0, 0, 72);
    m_mode2InvalidLineDisabledColor = QColor(0xFF, 0, 0, 30);

    m_vibratoButtonBorderColor = QColor(0xFF, 140, 0);
    m_vibratoButtonFillColor = QColor(0x232323);
    m_vibratoFrameColor = QColor(0x232323);

    m_ringWidth = 2;
    m_pointPadding = 2;
    m_pointRadius = 3;

    m_pointColor = Qt::red;
    m_ringColor = Qt::red;
}
