#pragma once

#include <mpi.h>
#include "ez_col_base.hpp"

namespace mmpi {
  template <typename A>
  struct ColMessage {
    ColMessage() {}

    MPI_Status get_status() { return m_status; }
    void set_comm(MPI_Comm comm) { m_comm = comm; }

    void bcast(int pid_root, A& buffer) {
      ez_bcast(pid_root, buffer, m_comm);
    }
    
    MPI_Status m_status;
    MPI_Comm m_comm = MPI_COMM_WORLD;
    
  };
};
