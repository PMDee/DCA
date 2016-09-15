// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Raffaele Solca' (rasolca@itp.phys.ethz.ch)
//
// This file tests the matrix operations with both Matrix<CPU> and Matrix<GPU>.

#include "dca/linalg/matrixop.hpp"
#include <complex>
#include <stdexcept>
#include <string>
#include <utility>
#include "gtest/gtest.h"
#include "dca/linalg/matrix.hpp"
#include "dca/linalg/blas/blas3.hpp"
#include "cpu_test_util.hpp"
#include "gpu_test_util.hpp"

#include "../src/comp_library/linalg/basic_cublas_functions.h"

TEST(MatrixopCPUGPUTest, difference) {
  std::pair<int, int> size2_a(5, 4);
  const double epsilon = std::numeric_limits<double>::epsilon();
  double diff = .01;

  auto val_a = [](int i, int j) { return 10 * i + j; };

  dca::linalg::Matrix<double, dca::linalg::CPU> a(size2_a);
  testing::setMatrixElements(a, val_a);
  dca::linalg::Matrix<double, dca::linalg::GPU> da(a);

  for (int sg : {1, -1})
    for (int ia : {0, 1, 4})
      for (int ja : {0, 2, 3}) {
        dca::linalg::Matrix<double, dca::linalg::CPU> b(a);
        b(ia, ja) += sg * diff;
        double err = std::abs(epsilon * b(ia, ja));

        EXPECT_NEAR(diff, dca::linalg::matrixop::difference(da, b, 2 * diff), err);
        EXPECT_NEAR(diff, dca::linalg::matrixop::difference(da, b, diff + err), err);
        auto diffcalc = dca::linalg::matrixop::difference(da, b, 2 * diff);
        EXPECT_NEAR(diff, dca::linalg::matrixop::difference(da, b, diffcalc), err);
        EXPECT_THROW(dca::linalg::matrixop::difference(da, b, diffcalc - err), std::logic_error);

        EXPECT_NEAR(diff, dca::linalg::matrixop::difference(b, da, 2 * diff), err);
        EXPECT_NEAR(diff, dca::linalg::matrixop::difference(b, da, diff + err), err);
        EXPECT_NEAR(diff, dca::linalg::matrixop::difference(b, da, diffcalc), err);
        EXPECT_THROW(dca::linalg::matrixop::difference(b, da, diffcalc - err), std::logic_error);
      }
}
