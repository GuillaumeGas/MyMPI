#pragma once

#include <mpi.h>

#include <mpiez/include/ez_col_base.hpp>
#if (__cplusplus >= 201103L)
#include <mpiez/include/ez_col_vector.hpp>
#endif
#include <mpiez/include/ez_col_array.hpp>

namespace mpiez {
  template <typename A>
  struct ColMessage {
    ColMessage() {
      set_comm(MPI_COMM_WORLD);
    }

    void set_comm(MPI_Comm comm) { 
      m_comm = comm; 
      MPI_Comm_rank(m_comm, &m_pid);
      MPI_Comm_size(m_comm, &m_nprocs);
    }

    void bcast(int root_pid, A& buffer) {
      ez_bcast(root_pid, buffer, m_comm);
    }

    void bcast(int root_pid, A* buffer, int size) {
      ez_bcast(root_pid, buffer, size, m_comm);
    }

    void scatter(int root_pid, A& send_buffer, A& recv_buffer, int tot_size) {
      ez_scatter(root_pid, send_buffer, recv_buffer, tot_size, m_nprocs, m_comm);
    }

    void scatter(int root_pid, A* send_buffer, A* recv_buffer, int tot_size) {
      ez_scatter(root_pid, send_buffer, recv_buffer, tot_size, m_nprocs, m_comm);
    }

    void scatterv(int root_pid, A& send_buffer, A& recv_buffer, int tot_size) {
      ez_scatterv(root_pid, send_buffer, recv_buffer, tot_size, m_pid, m_nprocs, m_comm);
    }

    void scatterv(int root_pid, A* send_buffer, A* recv_buffer, int tot_size) {
      ez_scatterv(root_pid, send_buffer, recv_buffer, tot_size, m_pid, m_nprocs, m_comm);
    }
    
    void gather(int root_pid, A& send_buffer, A& recv_buffer) {
      ez_gather(root_pid, send_buffer, recv_buffer, m_pid, m_nprocs, m_comm);
    }

    void gather(int root_pid, A* send_buffer, A* recv_buffer, int tot_size) {
      ez_gather(root_pid, send_buffer, recv_buffer, tot_size, m_nprocs, m_comm);
    }

    void gatherv(int root_pid, A& send_buffer, A& recv_buffer, int tot_size) {
      ez_gatherv(root_pid, send_buffer, recv_buffer, tot_size, m_pid, m_nprocs, m_comm);
    }

    void gatherv(int root_pid, A* send_buffer, A* recv_buffer, int tot_size) {
      ez_gatherv(root_pid, send_buffer, recv_buffer, tot_size, m_pid, m_nprocs, m_comm);
    }

    void allgather(A& send_buffer, A& recv_buffer) {
      ez_allgather(send_buffer, recv_buffer, m_nprocs, m_comm);
    }

    MPI_Comm m_comm;
    int m_pid;
    int m_nprocs;
  };
};
 
