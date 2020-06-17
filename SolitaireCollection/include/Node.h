#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
    public:
        T element;
        Node<T>* next;
        Node(T element, Node<T>*next=nullptr) {
        this->element=element;
        this->next=next;
        }

        Node(Node<T>*next=nullptr){                             //La clase nodo no tiene destructor?
        this->next=next;
        }
};

#endif // NODE_H
