#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"

class ExpressionList {
private:
    ExprNode* head;
    ExprNode* tail;
    int size;

public:
    ExpressionList();
    ~ExpressionList();
    
    void insert(std::string value, bool isOperator = false);
    ExprNode* getHead() const;
    bool empty() const;
    int getSize() const;
    void clear();
    void print() const;
};

#endif 