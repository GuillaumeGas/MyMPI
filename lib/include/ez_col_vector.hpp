#pragma once

#include <mpi.h>
#include <vector>

namespace mmpi {
  //TODO
  //void ez_bcast(int pid_root, std::vector<A>& buffer, MPI_Comm comm {}

  template<typename A>
  void ez_scatter(int pid_root, std::vector<A>& buffer_send, std::vector<A>& buffer_recv, int size, MPI_Comm comm) {
    buffer_recv.resize(size);
    MPI_Scatter(buffer_send.data(), size*sizeof(A), MPI_BYTE, buffer_recv.data(), size*sizeof(A), MPI_BYTE, pid_root, comm);
  }
};