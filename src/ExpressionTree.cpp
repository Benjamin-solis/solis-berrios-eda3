#include "../include/ExpressionTree.hpp"
#include "../include/Stack.hpp"
#include <iostream>

ExpressionTree::ExpressionTree() : root(nullptr) {}

ExpressionTree::~ExpressionTree() {
    deleteTree(root);
}

void ExpressionTree::deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

bool isOperatorFunc(const std::string& op) {
    return (op == "+" || op == "-" || op == "*" || op == "/" || op == "^" || op == "sqrt");
}

void ExpressionTree::buildFromPostfix(ExpressionList* postfixExpr) {
    Stack<TreeNode*> stack;
    ExprNode* current = postfixExpr->getHead();
    
    while (current != nullptr) {
        TreeNode* newNode = new TreeNode(current->value, current->isOperator);
        
        if (current->isOperator) {
            // sqrt es unario, solo necesita un operando
            if (current->value == "sqrt") {
                if (!stack.empty()) {
                    newNode->left = stack.top();
                    stack.pop();
                }
            } else {
                // Operadores binarios
                if (!stack.empty()) {
                    newNode->right = stack.top();
                    stack.pop();
                }
                if (!stack.empty()) {
                    newNode->left = stack.top();
                    stack.pop();
                }
            }
        }
        
        stack.push(newNode);
        current = current->next;
    }
    
    if (!stack.empty()) {
        root = stack.top();
        stack.pop();
    }
}

void ExpressionTree::printTree() const {
    if (root == nullptr) {
        std::cout << "Árbol vacío" << std::endl;
        return;
    }
    printTreeHelper(root, "", false);
}

void ExpressionTree::printTreeHelper(TreeNode* node, std::string prefix, bool isLeft) const {
    if (node == nullptr) return;
    
    std::cout << prefix;
    std::cout << (isLeft ? "├── " : "└── ");
    std::cout << node->value << std::endl;
    
    if (node->left != nullptr || node->right != nullptr) {
        if (node->left != nullptr) {
            printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
        }
        if (node->right != nullptr) {
            printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
        }
    }
}

void ExpressionTree::printPrefixNotation() const {
    if (root == nullptr) {
        std::cout << "Árbol vacío" << std::endl;
        return;
    }
    printPrefix(root);
    std::cout << std::endl;
}

void ExpressionTree::printPrefix(TreeNode* node) const {
    if (node == nullptr) return;
    
    std::cout << node->value << " ";
    printPrefix(node->left);
    printPrefix(node->right);
}

void ExpressionTree::printPostfixNotation() const {
    if (root == nullptr) {
        std::cout << "Árbol vacío" << std::endl;
        return;
    }
    printPostfix(root);
    std::cout << std::endl;
}

void ExpressionTree::printPostfix(TreeNode* node) const {
    if (node == nullptr) return;
    
    printPostfix(node->left);
    printPostfix(node->right);
    std::cout << node->value << " ";
}

TreeNode* ExpressionTree::getRoot() const {
    return root;
}