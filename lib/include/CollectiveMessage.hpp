#pragma once

#include <mpi.h>
#include "ez_col_base.hpp"
#include "ez_col_vector.hpp"

namespace mmpi {
  template <typename A>
  struct ColMessage {
    ColMessage() {}

    MPI_Status get_status() { return m_status; }
    void set_comm(MPI_Comm comm) { m_comm = comm; }

    void bcast(int pid_root, A& buffer) {
      ez_bcast(pid_root, buffer, m_comm);
    }

    void scatter(int pid_root, A& buffer_send, A& buffer_recv, int size) {
      ez_scatter(pid_root, buffer_send, buffer_recv, size, m_comm);
    }
    
    MPI_Status m_status;
    MPI_Comm m_comm = MPI_COMM_WORLD;
    
  };
};
