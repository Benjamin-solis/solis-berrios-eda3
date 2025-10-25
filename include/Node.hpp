#ifndef NODE_HPP
#define NODE_HPP

#include <string>

// Nodo genérico para listas enlazadas
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    
    Node(T value) : data(value), next(nullptr) {}
};

class ExprNode {
public:
    std::string value;
    bool isOperator;
    ExprNode* next;
    
    ExprNode(std::string val, bool isOp = false) 
        : value(val), isOperator(isOp), next(nullptr) {}
};

#endif 