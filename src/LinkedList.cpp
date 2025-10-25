#include "../include/LinkedList.hpp"
#include <iostream>

ExpressionList::ExpressionList() : head(nullptr), tail(nullptr), size(0) {}

ExpressionList::~ExpressionList() {
    clear();
}

void ExpressionList::insert(std::string value, bool isOperator) {
    ExprNode* newNode = new ExprNode(value, isOperator);
    
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

ExprNode* ExpressionList::getHead() const {
    return head;
}

bool ExpressionList::empty() const {
    return head == nullptr;
}

int ExpressionList::getSize() const {
    return size;
}

void ExpressionList::clear() {
    ExprNode* current = head;
    while (current != nullptr) {
        ExprNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}

void ExpressionList::print() const {
    ExprNode* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
}