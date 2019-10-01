//
// Created by Maxim on 28.09.2019.
//

#ifndef STRINGCALC_STACK_H
#define STRINGCALC_STACK_H

#include "stackElement.h"

template <typename T>
class stack {
private:
    StackElement<T> *head;
public:
    stack(){}
    inline bool empty() {
        return this->head != nullptr;
    }
    inline void push(T& newElement) {
        StackElement<T> *New = new StackElement<T>(newElement);
        New->prev = head;
        head = New;
        return;
    }
    inline void pop() {
        if (head == nullptr) return;
        StackElement<T>* Tmp = head;
        head = head->prev;
        delete Tmp;
    }
    inline T top() {
        if (head == nullptr) {
            throw ("Error : stack is empty, but you are trying to get a value of first element from it.");
        }
        return head->elem;
    }
};
#endif //STRINGCALC_STACK_H
