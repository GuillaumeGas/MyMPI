#pragma once

#include <mpi.h>

namespace mmpi {
  template <int N, typename A>
  struct Message {
    Message() {}

    void send(int pid_proc, A data) {
      MPI_Send(&data, sizeof(A), MPI_BYTE, pid_proc, N, MPI_COMM_WORLD);
    }

    void recv(int pid_proc, A* buffer) {
      MPI_Recv(buffer, sizeof(A), MPI_BYTE, pid_proc, N, MPI_COMM_WORLD, &m_status);
    }

    void send_array(int pid_proc, A* data, int size) {
      MPI_Send(data, size*sizeof(A), MPI_BYTE, pid_proc, N, MPI_COMM_WORLD);
    }

    void recv_array(int pid_proc, A* buffer, int size) {
      MPI_Recv(buffer, size*sizeof(A), MPI_BYTE, pid_proc, N, MPI_COMM_WORLD, &m_status);
    }

    MPI_Status get_status() { return m_status; }
    
    MPI_Status m_status;
  };
};
