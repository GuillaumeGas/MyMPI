#pragma once

#include <mpi.h>

namespace mmpi {
  template <int N, typename A>
  struct Message {
    Message() {}

    void send(int pid_proc, A data) {
      cout << "Send " << data << " to " << pid_proc << endl;
      MPI_Send(&data, sizeof(A), MPI_BYTE, pid_proc, N, MPI_COMM_WORLD);
    }

    void recv(int pid_proc, A * buffer) {
      cout << "Recv " << *buffer << " from " << pid_proc << endl;
      MPI_Recv(buffer, sizeof(A), MPI_BYTE, pid_proc, N, MPI_COMM_WORLD, &m_status);
    }

    MPI_Status get_status() { return m_status; }
    
    MPI_Status m_status;
  };
};
