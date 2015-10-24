#pragma once

#include <mpi.h>

namespace mpiez {
  template<typename A>
  void ez_send(int pid_proc, A& data, int tag, MPI_Comm comm) {
    MPI_Send(&data, sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_ssend(int pid_proc, A& data, int tag, MPI_Comm comm) {
    MPI_Ssend(&data, sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_bsend(int pid_proc, A& data, int tag, MPI_Comm comm) {
    int size;
    MPI_Pack_size(1, MPI_BYTE, comm, &size);
    size += MPI_BSEND_OVERHEAD;
    A* buffer = new A;
    MPI_Buffer_attach(buffer, size);
    MPI_Bsend(&data, sizeof(A), MPI_BYTE, pid_proc, tag, comm);
    MPI_Buffer_detach(buffer, &size);
    delete buffer;
  }
  
  template<typename A>
  void ez_recv(int pid_proc, A& data, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Recv(&data, sizeof(A), MPI_BYTE, pid_proc, tag, comm, &status);
  }

  template<typename A>
  void ez_send_recv(int pid_proc_send, int pid_proc_recv, A& data_send, A& data_recv, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Sendrecv(&data_send, sizeof(A), MPI_BYTE, pid_proc_send, tag, &data_recv, sizeof(A), MPI_BYTE, pid_proc_recv, tag, comm, &status);
  }

  template<typename A>
  void ez_send_recv_replace(int pid_proc_send, int pid_proc_recv, A& data, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Sendrecv_replace(&data, sizeof(A), MPI_BYTE, pid_proc_send, tag, pid_proc_recv, tag, comm, &status);
  }
};
