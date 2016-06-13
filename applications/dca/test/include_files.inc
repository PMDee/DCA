// File: include_files.h



// NFFT <--> DFT
const bool DO_NFFT = true;

// Concurrency
#include "dca/concurrency/concurrency.hpp"

//DCA data
#include "phys_library/DCA+_data/DCA_data.h"

//parameters
#include "phys_library/parameters/Parameters.h"

//DCA calculation
#include "phys_library/DCA+_loop/DCA+_loop.h"

// random number generator
#include "dca/math_library/random_number_library/ranq2.hpp"
using random_number_generator = rng::ranq2;

#include "phys_library/DCA+_step/cluster_solver/cluster_solver_mc_ctaux/ctaux_cluster_solver.h"

#include "comp_library/IO_library/JSON/JSON_writer.h"