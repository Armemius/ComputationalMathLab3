#pragma once

#ifndef COMPUTATIONALMATHLAB2_TG_HPP
#define COMPUTATIONALMATHLAB2_TG_HPP

#include "math/unary_operation.hpp"

class Tg : public Unary_operation {
public:
    explicit Tg(Expression *a);

    double process(std::unordered_map<std::string, double> &var_values) override;

    Expression *derivative(const std::string &variable) override;

    std::ostream &print(std::ostream &os) override;
};

#endif
