#pragma once

#include <mpi.h>
#include <vector>

#include <mpiez/include/ez_base.hpp>

namespace mpiez {
  template<typename A>
  void ez_send(int pid_proc, std::vector<A>& data, int tag, MPI_Comm comm) {
    MPI_Send(data.data(), data.size()*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_ssend(int pid_proc, std::vector<A>& data, int tag, MPI_Comm comm) {
    MPI_Ssend(data.data(), data.size()*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_bsend(int pid_proc, std::vector<A>& data, int tag, MPI_Comm comm) {
    int size;
    MPI_Pack_size(data.size(), MPI_BYTE, comm, &size);
    size += MPI_BSEND_OVERHEAD;
    A* buffer = new A[size*sizeof(A)];
    MPI_Buffer_attach(buffer, size);
    MPI_Bsend(data.data(), data.size()*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
    MPI_Buffer_detach(buffer, &size);
    delete[] buffer;
  }

  template<typename A>
  void ez_recv(int pid_proc, std::vector<A>& data, int tag, MPI_Comm comm, MPI_Status& status) {
    int size;
    MPI_Probe(pid_proc, tag, comm, &status);
    MPI_Get_count(&status, MPI_BYTE, &size);
    data.resize(size/sizeof(A));
    MPI_Recv(data.data(), size, MPI_BYTE, pid_proc, tag, comm, MPI_STATUS_IGNORE);
  }

  template<typename A>
  void ez_send_recv(int pid_proc_send, int pid_proc_recv, std::vector<A>& data_send, std::vector<A>& data_recv, int tag, MPI_Comm comm, MPI_Status& status, int send_size = -1, int recv_size = -1) {
    if(send_size == -1 && recv_size == -1) {
      send_size = data_send.size();
      recv_size = send_size;
    }
    data_recv.resize(recv_size);
    MPI_Sendrecv(data_send.data(), send_size*sizeof(A), MPI_BYTE, pid_proc_send, tag, data_recv.data(), recv_size*sizeof(A), MPI_BYTE, pid_proc_recv, tag, comm, MPI_STATUS_IGNORE);  
 }

  template<typename A>
  void ez_send_recv_replace(int pid_proc_send, int pid_proc_recv, std::vector<A>& data, int tag, MPI_Comm comm, MPI_Status& status) {
    MPI_Sendrecv_replace(data.data(), data.size()*sizeof(A), MPI_BYTE, pid_proc_send, tag, pid_proc_recv, tag, comm, &status);
  }
};
