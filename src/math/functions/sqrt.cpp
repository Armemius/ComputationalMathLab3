#include <cmath>
#include "math/functions/sqrt.hpp"

#include "math/constant.hpp"
#include "math/functions/divide.hpp"
#include "math/functions/multiply.hpp"

Sqrt::Sqrt(Expression *a) : Unary_operation(a) {}

double Sqrt::process(std::unordered_map<std::string, double> &var_values) {
  return std::sqrt(_a->process(var_values));
}

Expression *Sqrt::derivative(const std::string &variable) {
  return new Mult(new Div(new Const(1), new Mult(new Const(2), new Sqrt(this))), _a->derivative(variable));
}

std::ostream &Sqrt::print(std::ostream &os) {
  os << "sqrt(";
  _a->print(os);
  os << ")";
  return os;
}
