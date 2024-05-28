#pragma once

#ifndef COMPUTATIONALMATHLAB2_CONSTANT_HPP
#define COMPUTATIONALMATHLAB2_CONSTANT_HPP

#include "expression.hpp"

class Const final : public Expression {
    double _value;
public:
    explicit Const(double value);

    ~Const() override = default;

    double process(std::unordered_map<std::string, double> &var_values) override;

    Expression *derivative(const std::string &variable) override;

    std::ostream &print(std::ostream &os) override;
};

#endif
