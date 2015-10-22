#pragma once

#include <mpi.h>
#include "ez_base.hpp"
#include "ez_vector.hpp"
#include "ez_string.hpp"

namespace mmpi {
  template <int TAG, typename... Args>
  struct Message {
    Message() {}

    MPI_Status get_status() { return m_status; }
    void set_comm(MPI_Comm comm) { m_comm = comm; }
    
    void send(int pid_proc, Args& ... data) {
      send_(pid_proc, data...);
    }

    void recv(int pid_proc, Args& ... buffer) {
      recv_(pid_proc, buffer...);
    }

    void send_recv(int pid_proc_send, int pid_proc_recv, Args&... buffer_send, Args&... buffer_recv) {
      send_recv_(pid_proc_send, pid_proc_recv, buffer_send..., buffer_recv...);
    }

    
  private:
    void send_(int) {}
    
    template<typename T_, typename... Targs>
    void send_(int pid_proc, T_ & data, Targs&... args) {
      ez_send(pid_proc, data, TAG, m_comm);
      send_(pid_proc, args...);
    }

    void recv_(int) {}

    template<typename T_, typename... Targs>
    void recv_(int pid_proc, T_ & buffer, Targs&... args) {
      ez_recv(pid_proc, buffer, TAG, m_comm, m_status);
      recv_(pid_proc, args...);
    }
    
    void send_recv_(int, int) {}

    template<typename T_, typename... Targs>
    void send_recv_(int pid_proc_send, int pid_proc_recv, T_& buffer_send, T_& buffer_recv, Targs&... args) {
      ez_send_recv(pid_proc_send, pid_proc_recv, buffer_send, buffer_recv, TAG, m_comm, m_status);
      send_recv_(pid_proc_send, pid_proc_recv, args...);
    }

    MPI_Status m_status;
    MPI_Comm m_comm = MPI_COMM_WORLD;
  };
};
