#pragma once

#include <mpi.h>

namespace mpiez {
  namespace global {
    void barrier(MPI_Comm comm) {
      MPI_Barrier(comm);
    }
  }
};
