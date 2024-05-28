#include <cmath>
#include "math/functions/multiply.hpp"
#include "math/functions/power.hpp"
#include "math/functions/plus.hpp"
#include "math/functions/minus.hpp"
#include "math/constant.hpp"
#include "math/variable.hpp"
#include "math/functions/natural_log.hpp"
#include "math/functions/abs.hpp"

Pow::Pow(Expression *a, Expression *b) : Binary_operation(a, b) {}

double Pow::process(std::unordered_map<std::string, double> &var_values) {
    return pow(_a->process(var_values), _b->process(var_values));
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

Expression *Pow::derivative(const std::string &variable) {
    if (instanceof<Const>(_a)) {
        return new Mult(new Pow(_a, _b), new Mult(new Ln(new Abs(_a)), _b->derivative(variable)));
    }
    if (instanceof<Const>(_b)) {
        return new Mult(_b, new Mult(new Pow(_a, new Minus(_b, new Const(1))), _a->derivative(variable)));
    }
    return new Plus(new Mult(new Mult(_a->derivative(variable), _b), new Pow(_a, new Minus(_b, new Const(1)))),
                    new Mult(new Mult(new Pow(_a, _b), new Ln(new Abs(_a))), _b->derivative(variable)));
}

std::ostream &Pow::print(std::ostream &os) {
    os << "(";
    _a->print(os);
    os << " ^ ";
    _b->print(os);
    os << ")";
    return os;
}
