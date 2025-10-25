#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"
#include <stdexcept>

template <typename T>
class Stack {
private:
    Node<T>* topNode;
    int size;

public:
    Stack();
    ~Stack();

    void push(T value);
    void pop();
    T top() const;
    bool empty() const;
    int getSize() const;
    void clear();
};

// ----- Implementación -----

template <typename T>
Stack<T>::Stack() : topNode(nullptr), size(0) {}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
void Stack<T>::push(T value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = topNode;
    topNode = newNode;
    size++;
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Stack underflow: no se puede hacer pop en una pila vacía");
    }
    Node<T>* temp = topNode;
    topNode = topNode->next;
    delete temp;
    size--;
}

template <typename T>
T Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Stack vacía: no hay elemento en el top");
    }
    return topNode->data;
}

template <typename T>
bool Stack<T>::empty() const {
    return topNode == nullptr;
}

template <typename T>
int Stack<T>::getSize() const {
    return size;
}

template <typename T>
void Stack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

#endif
