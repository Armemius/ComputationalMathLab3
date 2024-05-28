#include "math/variable.hpp"
#include "math/constant.hpp"

#include <utility>

double Var::process(std::unordered_map<std::string, double> &var_values) {
    if (var_values.find(this->_name) == var_values.end()) {
        throw std::invalid_argument("Значение для переменной '" + this->_name + "' не предоставлено");
    }
    return var_values[this->_name];
}

Var::Var(std::string name) : _name(std::move(name)) {}

Expression *Var::derivative(const std::string &variable) {
    if (variable == this->_name) {
        return new Const(1);
    }
    return new Const(0);
}

std::ostream &Var::print(std::ostream &os) {
    os << this->_name;
    return os;
}

