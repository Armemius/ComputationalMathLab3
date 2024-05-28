#pragma once

#ifndef COMPUTATIONALMATHLAB2_UNARY_PLUS_HPP
#define COMPUTATIONALMATHLAB2_UNARY_PLUS_HPP

#include "math/unary_operation.hpp"

class U_plus : public Unary_operation {
public:
    explicit U_plus(Expression *a);

    double process(std::unordered_map<std::string, double> &var_values) override;

    Expression *derivative(const std::string &variable) override;

    std::ostream &print(std::ostream &os) override;
};

#endif
