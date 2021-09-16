#include "TrackButton.h"

TrackButton::TrackButton(QWidget *parent) : QPushButton(parent) {
}

TrackButton::TrackButton(const QString &text, QWidget *parent) : QPushButton(text, parent) {
}

TrackButton::~TrackButton() {
}
