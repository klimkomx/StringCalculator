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
    stack(){head = nullptr;}
    bool empty() {
        return head == nullptr;
    }
    void push(const T& newElement) {

        StackElement<T> *New = new StackElement<T>(newElement);
        if (head == nullptr)
            head = New;
        else {
            New->prev = head;
            head = New;
        }
        return;
    }
    void pop() {
        if (head == nullptr) return;
        StackElement<T>* Tmp = head;
        head = head->prev;
        delete Tmp;
    }
    T top() {
        if (head == nullptr) {
            throw ("Error : stack is empty, but you are trying to get a value of first element from it.");
        }
        return head->elem;
    }
};
#endif //STRINGCALC_STACK_H
