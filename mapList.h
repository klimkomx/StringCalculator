//
// Created by Maxim on 28.09.2019.
//

#ifndef MAPLIST_H
#define MAPLIST_H

#include <string>

template <typename T, typename D> class List {
public:
    List * next;
    T key;
    D element;
    List(T, D);
    List();
};

template <typename T> class List<T, char>{
public:
    List * next;
    T key;
    char element;
    List(T, char);
    List();
};

template <typename T> class List<T, std::string> {
public:
    List * next;
    T key;
    char element;
    List(T, std::string&);
    List();
};

template <typename T, typename D> List<T, D>::List() {
    element = D(0);
}

template <typename T, typename D> List<T, D>::List(T newKey, D newElement) {
    element = newElement;
    key = newKey;
}

template <typename T> List<T, char>::List() {
    element = char(0);
}

template <typename T> List<T, char>::List(T newKey, char newElement) {
    element = newElement;
    key = newKey;
}

template <typename T> List<T, std::string>::List() {
    element = "";
}

template <typename T> List<T, std::string>::List(T newKey, std::string& newElement) {
    element = newElement;
    key = newKey;
}

#endif //MAPLIST_H
