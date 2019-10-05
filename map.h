//
// Created by Maxim on 28.09.2019.
//

#ifndef MAP_H
#define MAP_H

#include <string>
#include "mapList.h"

namespace me {
//Constants
const int UNORDERED_MAP_LIST_SIZE = 100000, MULTIPLIER = 257;

//functions
template<typename T>
int hash(T &key) {
    return ((int)key) % UNORDERED_MAP_LIST_SIZE;
}

//map
template <typename T, typename D> class map {
private:
    List<T, D> *table[UNORDERED_MAP_LIST_SIZE];
    D& searchByKey(int, T&);
public:
    D& operator[](T);
};

template <typename T, typename D> D& map<T, D>::searchByKey(int index, T& sKey) {
    List<T, D> * tmp = table[index];

    if (tmp == nullptr) {
        table[index] = new List<T, D>();
        table[index] -> key = sKey;
        return table[index] -> element;
    }
    while (tmp->next != nullptr && tmp->key != sKey) tmp = tmp->next;
    if (tmp->key == sKey) return tmp->element;
    else {
        tmp->next = new List<T, D>();
        tmp->next->key = sKey;
        return tmp->next->element;
    }
}

template <typename T, typename D> D& map<T, D>::operator[](T key) {
    return searchByKey(hash(key), key);
}
}
#endif //MAP_H
