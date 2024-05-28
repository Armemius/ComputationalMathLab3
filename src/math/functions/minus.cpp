#include "math/functions/minus.hpp"

Minus::Minus(Expression *a, Expression *b) : Binary_operation(a, b) {}

double Minus::process(std::unordered_map<std::string, double> &var_values) {
    return _a->process(var_values) - _b->process(var_values);
}


Expression *Minus::derivative(const std::string &variable) {
    return new Minus(_a->derivative(variable), this->_b->derivative(variable));
}

std::ostream &Minus::print(std::ostream &os) {
    os << "(";
    _a->print(os);
    os << " - ";
    _b->print(os);
    os << ")";
    return os;
}
