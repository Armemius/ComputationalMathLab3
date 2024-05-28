#pragma once

#ifndef COMPUTATIONALMATHLAB2_BINARY_OPERATION_HPP
#define COMPUTATIONALMATHLAB2_BINARY_OPERATION_HPP

#include "expression.hpp"

class Binary_operation : public Expression {
protected:
    Expression *_a, *_b;
public:
    explicit Binary_operation(Expression *a, Expression *b);
    ~Binary_operation() override;
    double process(std::unordered_map<std::string, double> &var_values) override = 0;
    Expression *derivative(const std::string &variable) override = 0;
};

#endif
