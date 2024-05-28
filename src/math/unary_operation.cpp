#include "math/unary_operation.hpp"

#include "math/binary_operation.hpp"

Unary_operation::Unary_operation(Expression *a) : _a(a) {}

Expression *Unary_operation::derivative(const std::string &variable) {
    return nullptr;
}

Unary_operation::~Unary_operation() {
    delete _a;
}
