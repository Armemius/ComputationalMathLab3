#include "math/constant.hpp"

double Const::process(std::unordered_map<std::string, double> &var_values) {
    return this->_value;
}

Const::Const(double value) : _value(value) {}

Expression *Const::derivative(const std::string &variable) {
    return new Const(0);
}

std::ostream &Const::print(std::ostream &os) {
    os << this->_value;
    return os;
}
