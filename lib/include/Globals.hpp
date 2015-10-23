#pragma once

#include <mpi.h>

namespace mmpi {
  namespace global {
    void barrier(MPI_Comm comm) {
      MPI_Barrier(comm);
    }
  }
};
