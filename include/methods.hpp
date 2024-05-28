#pragma once

#include "math/expression.hpp"
#include <cmath>
#include <limits>

#include "math/functions/multiply.hpp"

inline bool does_converge(double a, double b, Expression *ex) {
  if (a > b) {
    std::swap(a, b);
  }
  Expression *der = ex->derivative("x");
  Expression *checker = new Mult(ex, der);

  const int steps = 1000;
  const double range = (b - a) / steps;

  for (int it = 0; it < steps; ++it) {
    std::unordered_map<std::string, double> value_curr = {
      {"x", it * range}
    };
    std::unordered_map<std::string, double> value_next = {
      {"x", it * range + range}
    };
    double curr_v = ex->process(value_curr);
    double next_v = ex->process(value_next);
    double curr_c = checker->process(value_curr);
    double next_c = checker->process(value_next);
    if (curr_c * next_c < 0) {
      if (std::abs(curr_v) > std::numeric_limits<double>::max() / 10) {
        return false;
      }
      if (std::abs(next_v) > std::numeric_limits<double>::max() / 10) {
        return false;
      }
    }
    if (std::isinf(curr_v) || std::isnan(curr_v) || std::isinf(next_v) || std::isnan(next_v)) {
      return false;
    }
  }
  return true;
}


inline double calculate_left_rect(double a, double b, int n, Expression *ex, bool output = true) {
  if (output)
    std::cout << "Using left rectangles method" << std::endl;
  if (a > b) {
    std::swap(a, b);
  }
  double range = (b - a) / n;
  if (output)
    std::cout << "Range size: " << range << std::endl;
  double res = 0;
  for (double it = a; it < b; it += range) {
    std::unordered_map<std::string, double> value = {
      {"x", it}
    };
    res += ex->process(value) * range;
  }
  if (output) {
    std::cout << "Result: " << res << std::endl;
    std::cout << "Calculation error: " << std::abs(calculate_left_rect(a, b, 2 * n, ex, false) - res) / 3<< std::endl;
  }
  return res;
}

inline double calculate_cent_rect(double a, double b, int n, Expression *ex, bool output = true) {
  if (output)
    std::cout << "Using central rectangles method" << std::endl;
  if (a > b) {
    std::swap(a, b);
  }
  double range = (b - a) / n;
  if (output)
    std::cout << "Range size: " << range << std::endl;
  double res = 0;
  for (double it = a; it < b; it += range) {
    std::unordered_map<std::string, double> value = {
      {"x", it + range / 2}
    };
    res += ex->process(value) * range;
  }
  if (output) {
    std::cout << "Result: " << res << std::endl;
    std::cout << "Calculation error: " << std::abs(calculate_cent_rect(a, b, 2 * n, ex, false) - res) / 3 << std::endl;
  }
  return res;
}

inline double calculate_right_rect(double a, double b, int n, Expression *ex, bool output = true) {
  if (output)
    std::cout << "Using right rectangles method" << std::endl;
  if (a > b) {
    std::swap(a, b);
  }
  double range = (b - a) / n;
  if (output)
    std::cout << "Range size: " << range << std::endl;
  double res = 0;
  for (double it = a; it < b; it += range) {
    std::unordered_map<std::string, double> value = {
      {"x", it + range}
    };
    res += ex->process(value) * range;
  }
  if (output) {
    std::cout << "Result: " << res << std::endl;
    std::cout << "Calculation error: " << std::abs(calculate_right_rect(a, b, 2 * n, ex, false) - res) / 3 << std::endl;
  }
  return res;
}

inline double calculate_trapezia(double a, double b, int n, Expression *ex, bool output = true) {
  if (output)
    std::cout << "Using trapezia method" << std::endl;
  if (a > b) {
    std::swap(a, b);
  }
  double range = (b - a) / n;
  if (output)
    std::cout << "Range size: " << range << std::endl;
  double res = 0;
  for (double it = a; it < b; it += range) {
    std::unordered_map<std::string, double> value = {
      {"x", it}
    };
    double f_x_1 = ex->process(value) * range;
    value = {
      {"x", it + range}
    };
    double f_x_2 = ex->process(value) * range;
    res += (f_x_1 + f_x_2) / 2;
  }
  if (output) {
    std::cout << "Result: " << res << std::endl;
    std::cout << "Calculation error: " << std::abs(calculate_trapezia(a, b, 2 * n, ex, false) - res) / 3 << std::endl;
  }
  return res;
}

inline double calculate_simpson(double a, double b, int n, Expression *ex, bool output = true) {
  if (output)
    std::cout << "Using Simpson's method" << std::endl;
  if (a > b) {
    std::swap(a, b);
  }
  if (n % 2 != 0) {
    n++;
    if (output)
      std::cout << "Adjusted number of intervals to " << n << " for Simpson's Rule" << std::endl;
  }
  const double range = (b - a) / n;
  if (output)
    std::cout << "Range size: " << range << std::endl;

  std::unordered_map<std::string, double> value = {
    {"x", a}
  };
  const double f_0 = ex->process(value); // f(x0)
  value = {{"x", b}};
  const double f_n = ex->process(value); // f(xn)

  double sum_odd = 0, sum_even = 0;
  for (int i = 1; i < n; i++) {
    value = {{"x", a + i * range}};
    const double f_x_i = ex->process(value);
    if (i % 2 == 0) {
      sum_even += f_x_i;
    } else {
      sum_odd += f_x_i;
    }
  }
  const double res = (range / 3) * (f_0 + 2 * sum_even + 4 * sum_odd + f_n);

  if (output) {
    std::cout << "Result: " << res << std::endl;
    std::cout << "Calculation error: " << std::abs(calculate_simpson(a, b, 2 * n, ex, false) - res) / 15 << std::endl;
  }
  return res;
}
