#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "LinkedList.hpp"
#include "ExpressionTree.hpp"
#include "Variable.hpp"
#include <string>
#include <vector>

class Calculator {
private:
    VariableManager varManager;
    ExpressionTree* lastTree;
    
    std::vector<std::string> tokenize(const std::string& input);
    ExpressionList* infixToPostfix(const std::vector<std::string>& tokens);
    double evaluatePostfix(ExpressionList* postfix);
    int getPrecedence(const std::string& op);
    bool isOperator(const std::string& token);
    bool isNumber(const std::string& token);
    double applyOperator(const std::string& op, double a, double b = 0);
    
public:
    Calculator();
    ~Calculator();
    
    void processInput(const std::string& input);
    void showVariable(const std::string& varName);
    void showTree();
    void showPrefix();
    void showPostfix();
};

#endif 