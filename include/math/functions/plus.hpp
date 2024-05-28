//
// Created by Armemius on 01.04.2024.
//

#ifndef COMPUTATIONALMATHLAB2_PLUS_HPP
#define COMPUTATIONALMATHLAB2_PLUS_HPP

#include "math/binary_operation.hpp"

class Plus : public Binary_operation {
public:
    Plus(Expression *a, Expression *b);
    double process(std::unordered_map<std::string, double> &var_values) override;
    Expression *derivative(const std::string &variable) override;
    std::ostream &print(std::ostream &os) override;
};

#endif
