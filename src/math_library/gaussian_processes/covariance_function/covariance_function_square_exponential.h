//-*-C++-*-

#ifndef MATH_LIBRARY_GAUSSIAN_PROCESSES_COVARIANCE_FUNCTION_COVARIANCE_FUNCTION_SQUARE_EXPONENTIAL_H
#define MATH_LIBRARY_GAUSSIAN_PROCESSES_COVARIANCE_FUNCTION_COVARIANCE_FUNCTION_SQUARE_EXPONENTIAL_H

#include <vector>
#include <iostream>
#include "comp_library/linalg/linalg.hpp"
#include "comp_library/function_plotting/include_plotting.h"
#include "math_library/gaussian_processes/covariance_function/covariance_function.h"

namespace math_algorithms {
namespace covariance_function {
// math_algorithms::covariance_function::

template <typename k_dmn_t>
class covariance_function<SQUARED_EXPONENTIAL, k_dmn_t> {
  const static int DIMENSION;

public:
  covariance_function();
  ~covariance_function();

  double execute(std::vector<double>& x_i);

  void plot();

public:
  double sigma_f;

  dca::linalg::Matrix<double, dca::linalg::CPU> A;
};

template <typename k_dmn_t>
const int covariance_function<SQUARED_EXPONENTIAL, k_dmn_t>::DIMENSION =
    k_dmn_t::parameter_type::DIMENSION;

template <typename k_dmn_t>
covariance_function<SQUARED_EXPONENTIAL, k_dmn_t>::covariance_function()
    : sigma_f(1.),

      A("A", std::pair<int, int>(DIMENSION, DIMENSION)) {
  for (int li = 0; li < DIMENSION; li++)
    A(li, li) = 1.;
}

template <typename k_dmn_t>
covariance_function<SQUARED_EXPONENTIAL, k_dmn_t>::~covariance_function() {}

template <typename k_dmn_t>
double covariance_function<SQUARED_EXPONENTIAL, k_dmn_t>::execute(std::vector<double>& x_i) {
  std::vector<double> y_i(DIMENSION, 0.);

  for (int li = 0; li < DIMENSION; li++)
    for (int lj = 0; lj < DIMENSION; lj++)
      y_i[li] += k_dmn_t::parameter_type::get_inverse_basis()[li + lj * DIMENSION] * x_i[lj];

  double result = 0;

  for (int li = 0; li < DIMENSION; li++)
    for (int lj = 0; lj < DIMENSION; lj++)
      result += y_i[li] * A(li, lj) * y_i[lj];

  return sigma_f * std::exp(-result);
}

template <typename k_dmn_t>
void covariance_function<SQUARED_EXPONENTIAL, k_dmn_t>::plot() {
  std::vector<double> x(0);
  std::vector<double> y(0);
  std::vector<double> z(0);

  std::vector<double> vec(DIMENSION, 0);

  switch (DIMENSION) {
    case 1: {
      for (int l = 0; l < k_dmn_t::dmn_size(); l++) {
        vec[0] = k_dmn_t::get_elements()[l];

        x.push_back(vec[0]);
        z.push_back(execute(vec));
      }

      SHOW::plot_points(x, z);
    } break;

    default:
      std::cout << __FUNCTION__ << std::endl;
  }
}

}  // covariance_function
}  // math_algorithm

#endif  // MATH_LIBRARY_GAUSSIAN_PROCESSES_COVARIANCE_FUNCTION_COVARIANCE_FUNCTION_SQUARE_EXPONENTIAL_H
