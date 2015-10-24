#pragma once

#include <mpi.h>

#include <mpiez/ez_col_base.hpp>
#include <mpiez/ez_col_vector.hpp>

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
    
    MPI_Comm m_comm = MPI_COMM_WORLD;
  };
};
