#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QDebug>
#include <QList>

template <class T>
class ItemList : public QList<T *> {
public:
    ItemList();

    int insertAuto(T *dragger);
    bool removeAuto(T *dragger);

    bool containsAuto(T *dragger);
    int findAuto(T *dragger, int *pos = nullptr);

private:
    int binarySearch(T *dragger);
};

template <class T>
ItemList<T>::ItemList() {
}

template <class T>
int ItemList<T>::insertAuto(T *dragger) {
    int index = binarySearch(dragger);
    if (index < 0 || index >= this->size() || this->at(index) != dragger) {
        this->insert(index, dragger);
        return index;
    } else {
        return -1;
    }
}

template <class T>
bool ItemList<T>::removeAuto(T *dragger) {
    int index = binarySearch(dragger);
    if (index < 0 || index >= this->size() || this->at(index) != dragger) {
        return false;
    } else {
        this->removeAt(index);
        return true;
    }
}

template <class T>
bool ItemList<T>::containsAuto(T *dragger) {
    return findAuto(dragger) >= 0;
}

template <class T>
int ItemList<T>::findAuto(T *dragger, int *pos) {
    int index = binarySearch(dragger);
    if (pos) {
        *pos = index;
    }
    if (index < 0 || index >= this->size() || this->at(index) != dragger) {
        return -1;
    }
    return index;
}

template <class T>
int ItemList<T>::binarySearch(T *dragger) {
    int i, j, mid;
    i = 0;
    j = this->size() - 1;
    while (i <= j) {
        mid = i + (j - i) / 2;
        if (*this->at(mid) < *dragger) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }
    return i;
}

#endif // ITEMLIST_H
