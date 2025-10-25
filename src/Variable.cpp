#include "../include/Variable.hpp"
#include <stdexcept>

VariableManager::VariableManager() {
}

void VariableManager::setVariable(const std::string& name, double value) {
    variables[name] = value;
}

double VariableManager::getVariable(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Variable no encontrada: " + name);
}

bool VariableManager::exists(const std::string& name) const {
    return variables.find(name) != variables.end();
}

void VariableManager::clear() {
    variables.clear();
}