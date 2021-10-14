#ifndef VIBRATOBASEHANDLE_H
#define VIBRATOBASEHANDLE_H

#include <QObject>

class NotesArea;
class Mode2Handler;

class VibratoObject : public QObject {
    Q_OBJECT
public:
    explicit VibratoObject(NotesArea *editor, Mode2Handler *scope);
    ~VibratoObject();

protected:
    NotesArea *m_editor;
    Mode2Handler *m_scope;

signals:
    void pressed();
    void moved();
    void clicked();
};

#endif // VIBRATOBASEHANDLE_H
