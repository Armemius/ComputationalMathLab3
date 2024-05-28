#pragma once

#ifndef COMPUTATIONALMATHLAB2_EXPRESSION_HPP
#define COMPUTATIONALMATHLAB2_EXPRESSION_HPP

#include <iostream>
#include <unordered_map>

class Expression {
public:
    virtual ~Expression() = default;
    virtual double process(std::unordered_map<std::string, double> &var_values) = 0;
    virtual Expression *derivative(const std::string &variable) = 0;
    virtual std::ostream &print(std::ostream &os) = 0;
};

#endif
