#ifndef MOVEOPERATION_H
#define MOVEOPERATION_H

#include "NoteOperation.h"

class MoveOperation : public NoteOperation {
public:
    MoveOperation();
    virtual ~MoveOperation();

    int movement() const;
    void setMovement(int movement);

    QList<int> verticals() const;
    void setVerticals(const QList<int> &verticals);

    int index() const;
    void setIndex(int index);

    virtual bool differ() const override;

private:
    int m_index;
    int m_movement;

    QList<int> m_verticals;
};

#endif // MOVEOPERATION_H
