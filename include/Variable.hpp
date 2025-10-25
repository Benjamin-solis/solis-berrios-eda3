#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>
#include <map>

class VariableManager {
private:
    std::map<std::string, double> variables;

public:
    VariableManager();
    
    void setVariable(const std::string& name, double value);
    double getVariable(const std::string& name) const;
    bool exists(const std::string& name) const;
    void clear();
};

#endif 