#pragma once

#ifndef COMPUTATIONALMATHLAB2_MINUS_HPP
#define COMPUTATIONALMATHLAB2_MINUS_HPP

#include "math/binary_operation.hpp"

class Minus : public Binary_operation {
public:
    Minus(Expression *a, Expression *b);
    double process(std::unordered_map<std::string, double> &var_values) override;
    Expression *derivative(const std::string &variable) override;
    std::ostream &print(std::ostream &os) override;
};

#endif
