// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Urs R. Haehner (haehneru@itp.phys.ethz.ch)
//
// This file tests double_counting_parameters.hpp
//
// TODO: Add tests for get_buffer_size, pack, unpack and writing.

#include "dca/phys/parameters/double_counting_parameters.hpp"
#include "gtest/gtest.h"
#include "dca/io/json/json_reader.hpp"

TEST(DoubleCountingParametersTest, DefaultValues) {
  dca::phys::params::DoubleCountingParameters pars;

  EXPECT_EQ("none", pars.get_double_counting_method());
  EXPECT_EQ(0., pars.get_double_counting_correction());
}

TEST(DoubleCountingParametersTest, ReadAll) {
  dca::io::JSONReader reader;
  dca::phys::params::DoubleCountingParameters pars;

  reader.open_file(DCA_SOURCE_DIR
                   "/test/unit/phys/parameters/double_counting_parameters/input_read_all.json");
  pars.readWrite(reader);
  reader.close_file();

  EXPECT_EQ("constant", pars.get_double_counting_method());
  EXPECT_EQ(42.1, pars.get_double_counting_correction());
}
