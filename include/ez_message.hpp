#pragma once

#include <mpi.h>

#include <mpiez/include/ez_base.hpp>
#if (__cplusplus >= 201103L)
#include <mpiez/include/ez_vector.hpp>
#endif
#include <mpiez/include/ez_string.hpp>
#include <mpiez/include/ez_array.hpp>

namespace mpiez {
  template <int TAG, typename T>
  struct Message {
    Message() {}

    MPI_Status get_status() { return m_status; }
    void set_comm(MPI_Comm comm) { m_comm = comm; }
    
    void send(int pid_proc, T& data) {
      ez_send(pid_proc, data, TAG, m_comm);
    }

    void send(int pid_proc, T* data, int size) {
      ez_send(pid_proc, data, size, TAG, m_comm);
    }

    void ssend(int pid_proc, T& data) {
      ez_ssend(pid_proc, data, TAG, m_comm);
    }

    void ssend(int pid_proc, T* data, int size) {
      ez_ssend(pid_proc, data, size, TAG, m_comm);
    }

    void bsend(int pid_proc, T& data) {
      ez_bsend(pid_proc, data, TAG, m_comm);
    }

    void bsend(int pid_proc, T* data, int size) {
      ez_bsend(pid_proc, data, size, TAG, m_comm);
    }

    void recv(int pid_proc, T & buffer) {
      ez_recv(pid_proc, buffer, TAG, m_comm, m_status);
    }

    void recv(int pid_proc, T* buffer, int size) {
      ez_recv(pid_proc, buffer, size, TAG, m_comm, m_status);
    }
    
    void send_recv(int pid_proc_send, int pid_proc_recv, T& buffer_send, T& buffer_recv) {
      ez_send_recv(pid_proc_send, pid_proc_recv, buffer_send, buffer_recv, TAG, m_comm, m_status);
    }

    void send_recv(int pid_proc_send, int pid_proc_recv, T* send_buffer, T* recv_buffer, int send_size, int recv_size) {
      ez_send_recv(pid_proc_send, pid_proc_recv, send_buffer, send_size, recv_buffer, recv_size, TAG, m_comm, m_status);
    }

    void send_recv_replace(int pid_proc_send, int pid_proc_recv, T& buffer) {
      ez_send_recv_replace(pid_proc_send, pid_proc_recv, buffer, TAG, m_comm, m_status);
    }

    void send_recv_replace(int pid_proc_send, int pid_proc_recv, T* buffer, int size) {
      ez_send_recv_replace(pid_proc_send, pid_proc_recv, buffer, size, TAG, m_comm, m_status);
    }

  private:
    MPI_Status m_status;
    MPI_Comm m_comm = MPI_COMM_WORLD;
  };
};
