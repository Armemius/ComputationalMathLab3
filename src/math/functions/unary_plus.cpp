#include "math/functions/unary_plus.hpp"

U_plus::U_plus(Expression *a) : Unary_operation(a) {}

double U_plus::process(std::unordered_map<std::string, double> &var_values) {
    return _a->process(var_values);
}

Expression *U_plus::derivative(const std::string &variable) {
    return _a->derivative(variable);
}

std::ostream &U_plus::print(std::ostream &os) {
    os << "+(";
    _a->print(os);
    os << ")";
    return os;
}

