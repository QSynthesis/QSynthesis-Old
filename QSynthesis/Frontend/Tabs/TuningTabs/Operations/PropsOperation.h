#ifndef PROPSOPERATION_H
#define PROPSOPERATION_H

#include "NoteOperation.h"

template <class T>
class PropsOperation : public NoteOperation {
public:
    PropsOperation();
    virtual ~PropsOperation();

    QList<T> origin() const;
    void setOrigin(const QList<T> &origin);

    QList<T> modified() const;
    void setModified(const QList<T> &modified);

    virtual bool differ() const override;

private:
    QList<T> m_origin;
    QList<T> m_modified;
};

template <class T>
PropsOperation<T>::PropsOperation() {
}

template <class T>
PropsOperation<T>::~PropsOperation() {
}

template <class T>
QList<T> PropsOperation<T>::origin() const {
    return m_origin;
}

template <class T>
void PropsOperation<T>::setOrigin(const QList<T> &origin) {
    m_origin = origin;
}

template <class T>
QList<T> PropsOperation<T>::modified() const {
    return m_modified;
}

template <class T>
void PropsOperation<T>::setModified(const QList<T> &modified) {
    m_modified = modified;
}


template <class T>
bool PropsOperation<T>::differ() const {
    return m_origin != m_modified;
}

#endif // PROPSOPERATION_H
