#pragma once

#include <mpi.h>
#include <vector>

namespace mpiez {
  template<typename A>
  void ez_bcast(int pid_root, std::vector<A>& buffer, MPI_Comm comm) {
    MPI_Bcast(buffer.data(), buffer.size()*sizeof(A), MPI_BYTE, pid_root, comm);
  }

  template<typename A>
  void ez_scatter(int pid_root, std::vector<A>& buffer_send, std::vector<A>& buffer_recv, int size, MPI_Comm comm) {
    buffer_recv.resize(size);
    MPI_Scatter(buffer_send.data(), size*sizeof(A), MPI_BYTE, buffer_recv.data(), size*sizeof(A), MPI_BYTE, pid_root, comm);
  }

  template <typename A>
  void ez_gather(int pid_root, std::vector<A>& buffer_send, std::vector<A>& buffer_recv, MPI_Comm comm) {
    MPI_Gather(buffer_send.data(), buffer_send.size()*sizeof(A), MPI_BYTE, buffer_recv.data(), buffer_send.size()*sizeof(A), MPI_BYTE, pid_root, comm); 
  }
};
