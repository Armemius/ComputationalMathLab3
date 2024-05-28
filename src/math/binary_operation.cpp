//
// Created by Armemius on 01.04.2024.
//
#include "math/binary_operation.hpp"

Binary_operation::Binary_operation(Expression *a, Expression *b) : _a(a), _b(b) {}

Binary_operation::~Binary_operation() {
    delete _a;
    delete _b;
}
