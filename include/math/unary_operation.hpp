#pragma once

#ifndef COMPUTATIONALMATHLAB2_UNARY_OPERATION_HPP
#define COMPUTATIONALMATHLAB2_UNARY_OPERATION_HPP

#include "expression.hpp"

class Unary_operation : public Expression {
protected:
    Expression *_a;
public:
    explicit Unary_operation(Expression *a);

    ~Unary_operation() override;

    double process(std::unordered_map<std::string, double> &var_values) override = 0;

    Expression *derivative(const std::string &variable) override = 0;
};

#endif
