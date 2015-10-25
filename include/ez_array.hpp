#pragma once

#include <mpi.h>

namespace mpiez {
  template <typename A>
  void ez_send(int pid_proc, A* data, int size, int tag, MPI_Comm comm) {
    MPI_Send(data, size*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template <typename A>
  void ez_ssend(int pid_proc, A* data, int size, int tag, MPI_Comm comm) {
    MPI_Ssend(data, size*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_bsend(int pid_proc, A* data, int size, int tag, MPI_Comm comm) {
    int buf_size;
    MPI_Pack_size(size, MPI_BYTE, comm, &buf_size);
    buf_size += MPI_BSEND_OVERHEAD;
    A* buffer = new A;
    MPI_Buffer_attach(buffer, buf_size);
    MPI_Bsend(&data, size*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
    MPI_Buffer_detach(buffer, &buf_size);
    delete buffer;
  }
  
  template<typename A>
  void ez_recv(int pid_proc, A* data, int size, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Recv(data, size*sizeof(A), MPI_BYTE, pid_proc, tag, comm, &status);
  }

  template<typename A>
  void ez_send_recv(int pid_proc_send, int pid_proc_recv, A* data_send, int size_send, A* data_recv, int size_recv, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Sendrecv(data_send, size_send*sizeof(A), MPI_BYTE, pid_proc_send, tag, data_recv, size_recv*sizeof(A), MPI_BYTE, pid_proc_recv, tag, comm, &status);
  }

  template<typename A>
  void ez_send_recv_replace(int pid_proc_send, int pid_proc_recv, A* data, int size, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Sendrecv_replace(data, size*sizeof(A), MPI_BYTE, pid_proc_send, tag, pid_proc_recv, tag, comm, &status);
  }
};
