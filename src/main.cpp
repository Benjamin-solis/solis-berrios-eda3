#include <iostream>
#include <string>
#include <sstream>
#include "../include/Calculator.hpp"

int main() {
    Calculator calc;
    std::string input;
    
    std::cout << "Bienvenido a EdaCal" << std::endl;
    
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        
        size_t start = input.find_first_not_of(" \t");
        size_t end = input.find_last_not_of(" \t");
        
        if (start == std::string::npos) {
            continue;
        }
        
        input = input.substr(start, end - start + 1);
        
        if (input.empty()) {
            continue;
        }
        
        if (input == "exit") {
            std::cout << "Saliendo de EdaCal..." << std::endl;
            break;
        }
        else if (input == "tree") {
            calc.showTree();
        }
        else if (input == "prefix") {
            calc.showPrefix();
        }
        else if (input == "postfix" || input == "posfix") {
            calc.showPostfix();
        }
        else if (input.substr(0, 5) == "show ") {
            std::string varName = input.substr(5);
            size_t varStart = varName.find_first_not_of(" \t");
            if (varStart != std::string::npos) {
                varName = varName.substr(varStart);
            }
            calc.showVariable(varName);
        }
        else {
            calc.processInput(input);
        }
    }
    
    return 0;
}