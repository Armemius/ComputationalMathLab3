#include <cmath>
#include "math/functions/sin.hpp"
#include "math/functions/cos.hpp"
#include "math/functions/multiply.hpp"

Sin::Sin(Expression *a) : Unary_operation(a) {}

double Sin::process(std::unordered_map<std::string, double> &var_values) {
    return sin(_a->process(var_values));
}

Expression *Sin::derivative(const std::string &variable) {
    return new Mult(new Cos(_a), _a->derivative(variable));
}

std::ostream &Sin::print(std::ostream &os) {
    os << "sin(";
    _a->print(os);
    os << ")";
    return os;
}
