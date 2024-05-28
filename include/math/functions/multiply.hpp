#pragma once

#ifndef COMPUTATIONALMATHLAB2_MULTIPLY_HPP
#define COMPUTATIONALMATHLAB2_MULTIPLY_HPP

#include "math/binary_operation.hpp"

class Mult : public Binary_operation {
public:
    Mult(Expression *a, Expression *b);
    double process(std::unordered_map<std::string, double> &var_values) override;
    Expression *derivative(const std::string &variable) override;
    std::ostream &print(std::ostream &os) override;
};

#endif
