#ifndef LIST_H
#define LIST_H

template <typename T> class listElem {
public:
    listElem<T>* next;
    T val;
    listElem(T elem) {
        next = nullptr;
        val = elem;
    }
    void clear() {
        if (next != nullptr) next -> clear();
        delete next;
        return;
    }
};

template<typename T> class list {
    listElem<T>* head;
public:
    void push(T newValue) {
        if (head == nullptr) {
            head = new listElem<T>(newValue);
            return;
        }
        listElem<T> *tmp = head;
        while (tmp -> next != nullptr) tmp = tmp -> next;
        tmp -> next = new listElem<T>(newValue);
    }
    void clear() {
        if (head != nullptr) head -> clear();
        delete head;
        return;
    }
};
#endif // LIST_H
