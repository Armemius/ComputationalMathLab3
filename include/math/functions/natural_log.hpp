#pragma once

#ifndef COMPUTATIONALMATHLAB2_NATURAL_LOG_HPP
#define COMPUTATIONALMATHLAB2_NATURAL_LOG_HPP

#include "math/unary_operation.hpp"

class Ln : public Unary_operation {
public:
    explicit Ln(Expression *a);
    double process(std::unordered_map<std::string, double> &var_values) override;
    Expression *derivative(const std::string &variable) override;
    std::ostream &print(std::ostream &os) override;
};

#endif
