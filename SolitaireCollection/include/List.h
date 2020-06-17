#ifndef LIST_H
#define LIST_H

template <typename T>

class List {
private:
    void operator =(const List&) {}


public:
    List() {}
    virtual ~List() {}
    virtual void insert(T element) = 0;
    virtual void append(T element) = 0;
    virtual T remove() = 0;
    virtual void clear() = 0;
    virtual T getElement() = 0;
    virtual void goToStart() = 0;
    virtual void goToEnd() = 0;
    virtual void goToPos(int pos) = 0;
    virtual void next() = 0;
    virtual bool atEnd() = 0;
    virtual void previous() = 0;
    virtual bool atStart() = 0;
    virtual int getPos() = 0;
    virtual int getSize() = 0;
    void virtual print(int x) = 0;
    void virtual goToLastElement() = 0;
};

#endif // LIST_H
