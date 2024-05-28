#include <cmath>
#include "math/functions/natural_log.hpp"
#include "math/functions/divide.hpp"
#include "math/constant.hpp"
#include "math/functions/multiply.hpp"

Ln::Ln(Expression *a) : Unary_operation(a) {}

double Ln::process(std::unordered_map<std::string, double> &var_values) {
    return log(_a->process(var_values));
}

Expression *Ln::derivative(const std::string &variable) {
    return new Mult(new Div(new Const(1), _a), _a->derivative(variable));
}

std::ostream &Ln::print(std::ostream &os) {
    os << "ln(";
    _a->print(os);
    os << ")";
    return os;
}
