// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Peter Staar (taa@zurich.ibm.com)
//         Urs R. Haehner (haehneru@itp.phys.ethz.ch)
//
// This class provides an interface to do a collective min with MPI.

#ifndef DCA_PARALLEL_MPI_CONCURRENCY_MPI_COLLECTIVE_MIN_HPP
#define DCA_PARALLEL_MPI_CONCURRENCY_MPI_COLLECTIVE_MIN_HPP

#include <mpi.h>
#include "dca/concurrency/mpi_concurrency/mpi_processor_grouping.hpp"
#include "dca/concurrency/mpi_concurrency/mpi_type_map.hpp"

namespace dca {
namespace concurrency {
// dca::concurrency::

class MPICollectiveMin {
public:
  MPICollectiveMin(const MPIProcessorGrouping& grouping) : grouping_(grouping) {}

  template <typename Scalar>
  void min(Scalar& value) const {
    Scalar result;

    MPI_Allreduce(&value, &result, MPITypeMap<Scalar>::factor(), MPITypeMap<Scalar>::value(),
                  MPI_MIN, grouping_.get());

    value = result;
  }

private:
  const MPIProcessorGrouping& grouping_;
};

}  // concurrency
}  // dca

#endif  // DCA_PARALLEL_MPI_CONCURRENCY_MPI_COLLECTIVE_MIN_HPP
