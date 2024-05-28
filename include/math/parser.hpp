#pragma once

#ifndef COMPUTATIONALMATHLAB2_PARSER_HPP
#define COMPUTATIONALMATHLAB2_PARSER_HPP

#include <queue>
#include <stack>
#include "math/functions/unary_plus.hpp"
#include "math/functions/abs.hpp"
#include "math/functions/minus.hpp"
#include "math/functions/divide.hpp"
#include "math/functions/natural_log.hpp"
#include "math/functions/cos.hpp"
#include "math/functions/sin.hpp"
#include "math/functions/tg.hpp"
#include "math/functions/multiply.hpp"
#include "math/functions/power.hpp"
#include "math/functions/plus.hpp"
#include "constant.hpp"
#include "variable.hpp"
#include "math/functions/unary_minus.hpp"

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

// Lower is higher
static std::unordered_map<char, int> priority = {
        {'^', 0},
        {'*', 1},
        {'/', 1},
        {'+', 2},
        {'-', 2},
};

bool is_numeric(char symbol) {
    return '0' <= symbol && symbol <= '9' || symbol == '.' || symbol == ',';
}

bool is_letter(char symbol) {
    return 'a' <= symbol && symbol <= 'z';
}

std::string read_word(const std::string &ex, int &pos) {
    std::string res;
    while (is_letter(ex[pos]) && pos < ex.size()) {
        res += ex[pos++];
    }
    return res;
}

std::string read_number(const std::string &ex, int &pos) {
    std::string res;
    while (is_numeric(ex[pos]) && pos < ex.size()) {
        res += ex[pos++];
    }
    return res;
}

Expression *parse(const std::string &ex) {
    std::unordered_map<std::string, double> empty_var = {};
    bool is_in_abs_expr = false;
    std::stack<std::string> stack;
    std::queue<std::string> result_exp_queue;
    std::stack<Expression *> result_stack;
    int pos = 0;
    while (pos != ex.size()) {
        if (is_numeric(ex[pos])) {
            result_exp_queue.emplace(read_number(ex, pos));
            continue;
        }
        if ((ex[pos] == '-' || ex[pos] == '+') && (pos == 0 || ex[pos - 1] == '(' || ex[pos - 1] == '|')) {
            if (ex[pos] == '-') {
                stack.emplace("u-");
            } else {
                stack.emplace("u+");
            }
            ++pos;
            continue;
        }
        if (is_letter(ex[pos])) {
            std::string word = read_word(ex, pos);
            if (word == "ln" || word == "cos" || word == "sin" || word == "tg") {
                stack.emplace(word);
                continue;
            }
            result_exp_queue.emplace(word);
            continue;
        }
        if (ex[pos] == '(') {
            stack.emplace("(");
            ++pos;
            continue;
        }
        if (ex[pos] == ')') {
            while (stack.top() != "(") {
                result_exp_queue.emplace(stack.top());
                stack.pop();
                if (stack.empty()) {
                    throw std::invalid_argument("Нет закрывающей скобки ')' в выражении");
                }
            }
            stack.pop();
            pos++;
            continue;
        }
        if (ex[pos] == '|') {
            if (!is_in_abs_expr) {
                stack.emplace("|");
                is_in_abs_expr = true;
            } else {
                while (stack.top() != "|") {
                    result_exp_queue.emplace(stack.top());
                    stack.pop();
                    if (stack.empty()) {
                        throw std::invalid_argument("Нет закрывающей скобки '|' в выражении");
                    }
                }
                stack.pop();
                result_exp_queue.emplace("abs");
                is_in_abs_expr = false;
            }
            ++pos;
            continue;
        }
        if (ex[pos] == '-' || ex[pos] == '+' || ex[pos] == '/' || ex[pos] == '*' || ex[pos] == '^') {
            while (!stack.empty() && (stack.top() == "u-" || stack.top() == "u+" || stack.top() == "ln" ||
                                      stack.top() == "cos" || stack.top() == "sin" || stack.top() == "tg" ||
                                      ((stack.top() == "-" || stack.top() == "+" || stack.top() == "/" ||
                                        stack.top() == "*" ||
                                        stack.top() == "^") && priority[stack.top()[0]] <= priority[ex[pos]]))) {
                result_exp_queue.emplace(stack.top());
                stack.pop();
                if (stack.empty()) {
                    break;
                }
            }
            stack.emplace(std::string{ex[pos++]});
        }
    }
    while (!stack.empty()) {
        result_exp_queue.emplace(stack.top());
        stack.pop();
    }

    while (!result_exp_queue.empty()) {
        const auto &op = result_exp_queue.front();
        result_exp_queue.pop();
        if (is_numeric(op[0])) {
            result_stack.push(new Const(std::stod(op)));
            continue;
        }
        if (is_letter(op[0]) &&
            (op != "ln" && op != "cos" && op != "sin" && op != "tg" && op != "abs" && op != "u+" && op != "u-")) {
            result_stack.push(new Var(op));
            continue;
        }
        if (op == "u+") {
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new U_plus(a));
            continue;
        }
        if (op == "u-") {
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new U_minus(a));
            continue;
        }
        if (op == "abs") {
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Abs(a));
            continue;
        }
        if (op == "+") {
            auto *b = result_stack.top();
            result_stack.pop();
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Plus(a, b));
            continue;
        }
        if (op == "-") {
            auto *b = result_stack.top();
            result_stack.pop();
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Minus(a, b));
            continue;
        }
        if (op == "/") {
            auto *b = result_stack.top();
            result_stack.pop();
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Div(a, b));
            continue;
        }
        if (op == "*") {
            auto *b = result_stack.top();
            result_stack.pop();
            auto *a = result_stack.top();
            result_stack.pop();
            if (instanceof<Const>(a)) {
                if (a->process(empty_var) == 0) {
                    result_stack.push(new Const(0));
                    continue;
                }
            }
            if (instanceof<Const>(b)) {
                if (b->process(empty_var) == 0) {
                    result_stack.push(new Const(0));
                    continue;
                }
            }
            result_stack.push(new Mult(a, b));
            continue;
        }
        if (op == "^") {
            auto *b = result_stack.top();
            result_stack.pop();
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Pow(a, b));
            continue;
        }
        if (op == "ln") {
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Ln(a));
            continue;
        }
        if (op == "cos") {
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Cos(a));
            continue;
        }
        if (op == "sin") {
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Sin(a));
            continue;
        }
        if (op == "tg") {
            auto *a = result_stack.top();
            result_stack.pop();
            result_stack.push(new Tg(a));
            continue;
        }
        result_exp_queue.pop();
    }

    return result_stack.top();
}


#endif
