#pragma once

#include <mpi.h>
#include "ez_base.hpp"
#include "ez_vector.hpp"
#include "ez_string.hpp"

namespace mmpi {
  template <int TAG, typename A>
  struct Message {
    Message() {}

    Message& send(int pid_proc, A & data) {
      ez_send(pid_proc, data, TAG, m_comm);
      return *this;
    }

    Message& recv(int pid_proc, A & buffer) {
      ez_recv(pid_proc, buffer, TAG, m_comm, m_status);
      return *this;
    }

    void send(int pid_proc, A & data, int size) {
      ez_send(pid_proc, data, size, TAG, m_comm);
    }

    void recv(int pid_proc, A & buffer, int size) {
      ez_recv(pid_proc, buffer, size, TAG, m_comm, &m_status);
    }

    MPI_Status get_status() { return m_status; }
    void set_comm(MPI_Comm comm) { m_comm = comm; }
    
    MPI_Status m_status;
    MPI_Comm m_comm = MPI_COMM_WORLD;
  };
};
