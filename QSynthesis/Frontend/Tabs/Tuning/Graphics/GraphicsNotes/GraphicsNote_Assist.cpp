#include "../../Editor/Areas/NotesArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsNote.h"

int GraphicsNote::convertTimeToTick(double time) const {
    double unit = 120.0 / m_tempo / 0.96;
    double prevUnit = m_prev ? (120.0 / m_prev->m_tempo / 0.96) : unit;
    double tick = (time < 0) ? (time / prevUnit) : (time / unit);

    return tick;
}

double GraphicsNote::convertTickToTime(double tick) const {
    double unit = 120.0 / m_tempo / 0.96;
    double prevUnit = m_prev ? (120.0 / m_prev->m_tempo / 0.96) : unit;
    double time = (tick < 0) ? (tick * prevUnit) : (tick * unit);

    return time;
}
