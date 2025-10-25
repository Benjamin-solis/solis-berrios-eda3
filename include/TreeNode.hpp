#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <string>

class TreeNode {
public:
    std::string value;
    bool isOperator;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(std::string val, bool isOp = false) 
        : value(val), isOperator(isOp), left(nullptr), right(nullptr) {}
};

#endif 