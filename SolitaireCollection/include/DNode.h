#ifndef DNODE_H
#define DNODE_H

template <typename T>

class DNode
{
    public:
        T element;
        DNode<T> *next;
        DNode<T> *previous;

        DNode(T element, DNode<T> *next = nullptr, DNode<T>* previous = nullptr) {
        this->element=element;
        this->next=next;
        this->previous=previous;
        }

        DNode(DNode<T> * next = nullptr, DNode<T> * previous = nullptr){
        this->next=next;
        this->previous=previous;

        }

};

#endif // DNODE_H
