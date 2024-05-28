#include "math/functions/plus.hpp"

Plus::Plus(Expression *a, Expression *b) : Binary_operation(a, b) {}

double Plus::process(std::unordered_map<std::string, double> &var_values) {
    return _a->process(var_values) + this->_b->process(var_values);
}


Expression *Plus::derivative(const std::string &variable) {
    return new Plus(_a->derivative(variable), this->_b->derivative(variable));
}

std::ostream &Plus::print(std::ostream &os) {
    os << "(";
    _a->print(os);
    os << " + ";
    _b->print(os);
    os << ")";
    return os;
}
