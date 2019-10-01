//
// Created by Maxim on 28.09.2019.
//

#ifndef STACKELEMENT_H
#define STACKELEMENT_H

template <typename T>
class StackElement {
public:
    StackElement * prev;
    T elem;
    StackElement(T new_elem){
        elem = new_elem;
        prev = nullptr;
    }
};
#endif //STACKELEMENT_H
