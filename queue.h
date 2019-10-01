//
// Created by Maxim on 01.10.2019.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "queueElement.h"

template <typename T>
class queue {
private:
    QueueElement<T> *head, *tail;
public:
    queue(){
        head = nullptr, tail = nullptr;
    }
    inline bool empty() {
        return head != nullptr;
    }
    inline void push(T& newElement) {
        QueueElement<T> *New = new QueueElement<T>(newElement);
        if (head != nullptr) tail->next = New;
        else head = New;
        tail = New;
        return;
    }
    inline void pop() {
        QueueElement<T>* Tmp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete Tmp;
    }
    inline T top() {
        return head->elem;
    }
};

#endif //QUEUE_H
