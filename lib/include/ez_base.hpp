#pragma once

#include <mpi.h>

namespace mmpi {
  template<typename A>
  void ez_send(int pid_proc, A& data, int tag, MPI_Comm comm) {
    MPI_Send(&data, sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_recv(int pid_proc, A& data, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Recv(&data, sizeof(A), MPI_BYTE, pid_proc, tag, comm, &status);
  }

  template<typename A>
  void ez_send_recv(int pid_proc_send, int pid_proc_recv, A& data_send, A& data_recv, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Sendrecv(&data_send, sizeof(A), MPI_BYTE, pid_proc_recv, tag, &data_recv, sizeof(A), MPI_BYTE, pid_proc_send, tag, comm, &status);
  }
};
