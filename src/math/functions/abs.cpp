#include "math/functions/abs.hpp"
#include "math/functions/divide.hpp"
#include "math/functions/multiply.hpp"

Abs::Abs(Expression *a) : Unary_operation(a) {}

double Abs::process(std::unordered_map<std::string, double> &var_values) {
    return std::abs(_a->process(var_values));
}

Expression *Abs::derivative(const std::string &variable) {
    return new Div(new Mult(_a, _a->derivative(variable)), new Abs(_a));
}

std::ostream &Abs::print(std::ostream &os) {
    os << '|';
    _a->print(os);
    os << "|";
    return os;
}
