#include "../../Params/Areas/LiftersArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../TuningGroup.h"
#include "../GraphicsLifter.h"

void GraphicsLifter::fromNoteProps(GraphicsLifter::Props prop) {
    switch (prop) {
    case Intensity:
        m_values[Intensity] = m_note->intensity();
        break;
    case Modulation:
        m_values[Modulation] = m_note->modulation();
        break;
    case Velocity:
        m_values[Velocity] = m_note->velocity();
        break;
    default:
        fromNoteProps(Intensity);
        fromNoteProps(Modulation);
        fromNoteProps(Velocity);
        break;
    }
}

void GraphicsLifter::toNoteProps(GraphicsLifter::Props prop) {
    switch (prop) {
    case Intensity:
        m_note->Note.intensity = m_values[Intensity];
        break;
    case Modulation:
        m_note->Note.modulation = m_values[Modulation];
        break;
    case Velocity:
        m_note->Note.velocity = m_values[Velocity];
        break;
    default:
        toNoteProps(Intensity);
        toNoteProps(Modulation);
        toNoteProps(Velocity);
        break;
    }
}

void GraphicsLifter::setValue(double value) {
    GraphicsLineHandle::setValue(value);

    if (value > 1 || value < 0) {
        setActive(false);
    } else {
        setActive(true);
    }
}
