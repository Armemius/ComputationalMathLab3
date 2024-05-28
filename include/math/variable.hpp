#pragma once

#ifndef COMPUTATIONALMATHLAB2_VARIABLE_HPP
#define COMPUTATIONALMATHLAB2_VARIABLE_HPP

#include "expression.hpp"

class Var final : public Expression {
    std::string _name;
public:
    explicit Var(std::string name);

    ~Var() override = default;

    double process(std::unordered_map<std::string, double> &var_values) override;

    Expression *derivative(const std::string &variable) override;
    std::ostream &print(std::ostream &os) override;
};

#endif
