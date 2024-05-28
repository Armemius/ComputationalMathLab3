#include "math/functions/unary_minus.hpp"

U_minus::U_minus(Expression *a) : Unary_operation(a) {}

double U_minus::process(std::unordered_map<std::string, double> &var_values) {
    return -_a->process(var_values);
}

Expression *U_minus::derivative(const std::string &variable) {
    return new U_minus(_a->derivative(variable));
}

std::ostream &U_minus::print(std::ostream &os) {
    os << "-(";
    _a->print(os);
    os << ")";
    return os;
}

