#pragma once

#ifndef COMPUTATIONALMATHLAB2_UNARY_MINUS_HPP
#define COMPUTATIONALMATHLAB2_UNARY_MINUS_HPP

#include "math/unary_operation.hpp"

class U_minus : public Unary_operation {
public:
    explicit U_minus(Expression *a);
    double process(std::unordered_map<std::string, double> &var_values) override;
    Expression *derivative(const std::string &variable) override;
    std::ostream &print(std::ostream &os) override;
};

#endif
