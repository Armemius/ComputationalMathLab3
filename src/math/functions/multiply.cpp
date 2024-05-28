#include "math/functions/multiply.hpp"
#include "math/functions/plus.hpp"

Mult::Mult(Expression *a, Expression *b) : Binary_operation(a, b) {}

double Mult::process(std::unordered_map<std::string, double> &var_values) {
    return _a->process(var_values) * _b->process(var_values);
}

Expression *Mult::derivative(const std::string &variable) {
    return new Plus(new Mult(_a->derivative(variable), _b), new Mult(_a, _b->derivative(variable)));
}

std::ostream &Mult::print(std::ostream &os) {
    os << "(";
    _a->print(os);
    os << " * ";
    _b->print(os);
    os << ")";
    return os;
}
