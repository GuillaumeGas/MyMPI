#pragma once

#include <mpi.h>

namespace mpiez {
  template<typename A>
  void ez_bcast(int pid_root, A& buffer, MPI_Comm comm) {
    MPI_Bcast(&buffer, sizeof(A), MPI_BYTE, pid_root, comm);
  }
};
