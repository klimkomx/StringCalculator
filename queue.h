//
// Created by Maxim on 01.10.2019.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "queueElement.h"
#include<QDebug>
template <typename T>
class queue {
private:
    QueueElement<T> *head, *tail;
public:
    queue(){
        head = nullptr, tail = nullptr;
    }
    bool empty()const {
        return (head == nullptr);
    }
    inline void push(const T& newElement) {
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
    inline T front() {
        return head->elem;
    }
    void clear() {
        QueueElement<T> *tmp = head, *tmp2;
        while (tmp != nullptr) {
            qDebug() << "kek";
            tmp2 = tmp -> next;
            qDebug() << "go";
            delete tmp;
            qDebug() << "gog";
            tmp = tmp2;
        }
        return;
    }
};

#endif //QUEUE_H
