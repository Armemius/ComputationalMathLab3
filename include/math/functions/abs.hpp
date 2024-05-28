#pragma once

#ifndef COMPUTATIONALMATHLAB2_ABS_HPP
#define COMPUTATIONALMATHLAB2_ABS_HPP

#include "math/unary_operation.hpp"

class Abs : public Unary_operation {
public:
    explicit Abs(Expression *a);
    double process(std::unordered_map<std::string, double> &var_values) override;
    Expression *derivative(const std::string &variable) override;
    std::ostream &print(std::ostream &os) override;
};

#endif
