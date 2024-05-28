#include <cmath>
#include "math/functions/tg.hpp"
#include "math/functions/multiply.hpp"
#include "math/functions/divide.hpp"
#include "math/constant.hpp"
#include "math/functions/cos.hpp"

Tg::Tg(Expression *a) : Unary_operation(a) {}

double Tg::process(std::unordered_map<std::string, double> &var_values) {
    return tan(_a->process(var_values));
}

Expression *Tg::derivative(const std::string &variable) {
    return new Mult(new Div(new Const(1), new Mult(new Cos(_a), new Cos(_a))), _a->derivative(variable));
}

std::ostream &Tg::print(std::ostream &os) {
    os << "tg(";
    _a->print(os);
    os << ")";
    return os;
}


