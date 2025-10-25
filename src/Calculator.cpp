#include "../include/Calculator.hpp"
#include "../include/Stack.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <cctype>
#include <algorithm>

Calculator::Calculator() : lastTree(nullptr) {

    varManager.setVariable("ans", 0);
}

Calculator::~Calculator() {
    if (lastTree != nullptr) {
        delete lastTree;
    }
}

std::vector<std::string> Calculator::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

bool Calculator::isOperator(const std::string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || 
            token == "^" || token == "sqrt");
}

bool Calculator::isNumber(const std::string& token) {
    if (token.empty()) return false;
    
    size_t start = 0;
    if (token[0] == '-' || token[0] == '+') {
        if (token.length() == 1) return false;
        start = 1;
    }
    
    bool hasDecimal = false;
    for (size_t i = start; i < token.length(); i++) {
        if (token[i] == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        } else if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

int Calculator::getPrecedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    if (op == "sqrt") return 4;
    return 0;
}

ExpressionList* Calculator::infixToPostfix(const std::vector<std::string>& tokens) {
    Stack<std::string> opStack;
    ExpressionList* postfix = new ExpressionList();
    
    for (size_t i = 0; i < tokens.size(); i++) {
        std::string token = tokens[i];
        
        
        if (isNumber(token)) {
            postfix->insert(token, false);
        }
        else if (!isOperator(token) && token != "(" && token != ")") {
            if (varManager.exists(token)) {
                double val = varManager.getVariable(token);
                postfix->insert(std::to_string(val), false);
            } else {
                std::cout << "Error: variable '" << token << "' no definida" << std::endl;
                delete postfix;
                return nullptr;
            }
        }
        else if (token == "(") {
            opStack.push(token);
        }
        else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                postfix->insert(opStack.top(), true);
                opStack.pop();
            }
            if (!opStack.empty()) {
                opStack.pop(); 
            }
        }
        else if (isOperator(token)) {
            while (!opStack.empty() && opStack.top() != "(" && 
                   getPrecedence(token) <= getPrecedence(opStack.top())) {
                postfix->insert(opStack.top(), true);
                opStack.pop();
            }
            opStack.push(token);
        }
    }
    
    while (!opStack.empty()) {
        postfix->insert(opStack.top(), true);
        opStack.pop();
    }
    
    return postfix;
}

double Calculator::applyOperator(const std::string& op, double a, double b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) {
            std::cout << "Error: división por cero" << std::endl;
            return 0;
        }
        return a / b;
    }
    if (op == "^") return pow(a, b);
    if (op == "sqrt") return sqrt(a);
    return 0;
}

double Calculator::evaluatePostfix(ExpressionList* postfix) {
    Stack<double> values;
    ExprNode* current = postfix->getHead();
    
    while (current != nullptr) {
        if (!current->isOperator) {
            values.push(std::stod(current->value));
        } else {
            if (current->value == "sqrt") {
                if (!values.empty()) {
                    double val = values.top();
                    values.pop();
                    values.push(applyOperator(current->value, val));
                }
            } else {
                if (!values.empty()) {
                    double v2 = values.top();
                    values.pop();
                    if (!values.empty()) {
                        double v1 = values.top();
                        values.pop();
                        values.push(applyOperator(current->value, v1, v2));
                    }
                }
            }
        }
        current = current->next;
    }
    
    return values.empty() ? 0 : values.top();
}

void Calculator::processInput(const std::string& input) {
    std::vector<std::string> tokens = tokenize(input);
    
    if (tokens.empty()) return;
    
    std::string varName = "ans";
    size_t exprStart = 0;
    
    if (tokens.size() >= 3 && tokens[1] == "=") {
        varName = tokens[0];
        exprStart = 2;
    }
    
    std::vector<std::string> exprTokens(tokens.begin() + exprStart, tokens.end());
    
    ExpressionList* postfix = infixToPostfix(exprTokens);
    if (postfix == nullptr) return;
    
    double result = evaluatePostfix(postfix);
    
    varManager.setVariable(varName, result);
    
    std::cout << ">> " << varName << " -> " << result << std::endl;
    
    if (lastTree != nullptr) {
        delete lastTree;
    }
    lastTree = new ExpressionTree();
    lastTree->buildFromPostfix(postfix);
    
    delete postfix;
}

void Calculator::showVariable(const std::string& varName) {
    if (varManager.exists(varName)) {
        double value = varManager.getVariable(varName);
        std::cout << ">> " << varName << " -> " << value << std::endl;
    } else {
        std::cout << "Error: variable '" << varName << "' no definida" << std::endl;
    }
}

void Calculator::showTree() {
    if (lastTree != nullptr) {
        lastTree->printTree();
    } else {
        std::cout << "No hay árbol de expresión disponible" << std::endl;
    }
}

void Calculator::showPrefix() {
    if (lastTree != nullptr) {
        std::cout << ">> ";
        lastTree->printPrefixNotation();
    } else {
        std::cout << "No hay expresión disponible" << std::endl;
    }
}

void Calculator::showPostfix() {
    if (lastTree != nullptr) {
        std::cout << ">> ";
        lastTree->printPostfixNotation();
    } else {
        std::cout << "No hay expresión disponible" << std::endl;
    }
}