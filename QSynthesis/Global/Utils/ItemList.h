#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QDebug>
#include <QList>

template <class T>
class ItemList : public QList<T *> {
public:
    ItemList();

    int insertAuto(T *item);
    bool removeAuto(T *item);

    bool containsAuto(T *item);
    int findAuto(T *item, int *pos = nullptr);

private:
    int binarySearch(T *item);
};

template <class T>
ItemList<T>::ItemList() {
}

template <class T>
int ItemList<T>::insertAuto(T *item) {
    int index = binarySearch(item);
    if (index < 0 || index >= this->size() || this->at(index) != item) {
        this->insert(index, item);
        return index;
    } else {
        return -1;
    }
}

template <class T>
bool ItemList<T>::removeAuto(T *item) {
    int index = binarySearch(item);
    if (index < 0 || index >= this->size() || this->at(index) != item) {
        return false;
    } else {
        this->removeAt(index);
        return true;
    }
}

template <class T>
bool ItemList<T>::containsAuto(T *item) {
    return findAuto(item) >= 0;
}

template <class T>
int ItemList<T>::findAuto(T *item, int *pos) {
    int index = binarySearch(item);
    if (pos) {
        *pos = index;
    }
    if (index < 0 || index >= this->size() || this->at(index) != item) {
        return -1;
    }
    return index;
}

template <class T>
int ItemList<T>::binarySearch(T *item) {
    int i, j, mid;
    i = 0;
    j = this->size() - 1;
    if (!this || !item) {
        return -1;
    }
    while (i <= j) {
        mid = i + (j - i) / 2;
        if (*this->at(mid) < *item) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }
    return i;
}

#endif // ITEMLIST_H
