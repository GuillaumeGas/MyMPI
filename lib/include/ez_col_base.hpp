#pragma once

#include <mpi.h>

namespace mmpi {
  template<typename T>
  void ez_bcast(int pid_root, A& buffer, MPI_Comm comm) {
    MPI_Bcast(&buffer, sizeof(A), MPI_BYTE, pid_root, comm);
  }
};
