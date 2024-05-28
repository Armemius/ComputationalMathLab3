#include "math/functions/divide.hpp"
#include "math/functions/minus.hpp"
#include "math/functions/multiply.hpp"

Div::Div(Expression *a, Expression *b) : Binary_operation(a, b) {}

double Div::process(std::unordered_map<std::string, double> &var_values) {
    return _a->process(var_values) / _b->process(var_values);
}

Expression *Div::derivative(const std::string &variable) {
    return new Div(new Minus(new Mult(_a->derivative(variable), _b), new Mult(_a, _b->derivative(variable))),
                   new Mult(_b, _b));
}

std::ostream &Div::print(std::ostream &os) {
    os << "(";
    _a->print(os);
    os << " / ";
    _b->print(os);
    os << ")";
    return os;
}


