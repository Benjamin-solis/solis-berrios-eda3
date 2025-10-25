#ifndef EXPRESSIONTREE_HPP
#define EXPRESSIONTREE_HPP

#include "TreeNode.hpp"
#include "LinkedList.hpp"
#include <string>

class ExpressionTree {
private:
    TreeNode* root;
    
    void printTreeHelper(TreeNode* node, std::string prefix, bool isLeft) const;
    void deleteTree(TreeNode* node);
    void printPrefix(TreeNode* node) const;
    void printPostfix(TreeNode* node) const;

public:
    ExpressionTree();
    ~ExpressionTree();
    
    void buildFromPostfix(ExpressionList* postfixExpr);
    void printTree() const;
    void printPrefixNotation() const;
    void printPostfixNotation() const;
    TreeNode* getRoot() const;
};

#endif 