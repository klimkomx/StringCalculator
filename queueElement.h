//
// Created by Maxim on 01.10.2019.
//

#ifndef QUEUEELEMENT_H
#define QUEUEELEMENT_H

template <typename T>
class QueueElement {
public:
    QueueElement *next;
    T elem;
    QueueElement(T new_elem){
        elem = new_elem;
        next= nullptr;
    }
};

#endif //QUEUEELEMENT_H
