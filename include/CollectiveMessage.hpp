#pragma once

#include <mpi.h>

#include <mpiez/include/ez_col_base.hpp>
#include <mpiez/include/ez_col_vector.hpp>

namespace mpiez {
  template <typename A>
  struct ColMessage {
    ColMessage() {}

    void set_comm(MPI_Comm comm) { m_comm = comm; }

    void bcast(int pid_root, A& buffer) {
      ez_bcast(pid_root, buffer, m_comm);
    }

    void scatter(int pid_root, A& buffer_send, A& buffer_recv, int size) {
      ez_scatter(pid_root, buffer_send, buffer_recv, size, m_comm);
    }
    
    void gather(int pid_root, A& buffer_send, A& buffer_recv) {
      ez_gather(pid_root, buffer_send, buffer_recv, m_comm);
    }

    MPI_Comm m_comm = MPI_COMM_WORLD;
  };
};
