#pragma once

#include <mpi.h>

namespace mmpi {
  template<typename A>
  void ez_send(int pid_proc, A& data, int tag, MPI_Comm comm) {
    MPI_Send(&data, sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_recv(int pid_proc, A& data, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Recv(&data, sizeof(A), MPI_BYTE, pid_proc, tag, comm, &status);
  }
};
