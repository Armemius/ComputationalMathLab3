#include <cmath>
#include "math/functions/cos.hpp"
#include "math/functions/unary_minus.hpp"
#include "math/functions/sin.hpp"
#include "math/functions/multiply.hpp"

Cos::Cos(Expression *a) : Unary_operation(a) {}

double Cos::process(std::unordered_map<std::string, double> &var_values) {
    return cos(_a->process(var_values));
}

Expression *Cos::derivative(const std::string &variable) {
    return new Mult(new U_minus(new Sin(_a)), _a->derivative(variable));
}

std::ostream &Cos::print(std::ostream &os) {
    os << "cos(";
    _a->print(os);
    os << ")";
    return os;
}

