#pragma once

#include <mpi.h>
#include <vector>
#include "ez_base.hpp"

namespace mmpi {
  template<typename A>
  void ez_send(int pid_proc, std::vector<A>& data, int tag, MPI_Comm comm) {
    MPI_Send(data.data(), data.size()*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_ssend(int pid_proc, std::vector<A>& data, int tag, MPI_Comm comm) {
    MPI_Ssend(data.date(), data.size()*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
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
  void ez_send_recv(int pid_proc_send, int pid_proc_recv, std::vector<A>& data_send, std::vector<A>& data_recv, int tag, MPI_Comm comm, MPI_Status& status) {
    int size = data_send.size();
    MPI_Sendrecv(data_send.data(), size*sizeof(A), MPI_BYTE, pid_proc_send, tag, data_recv.data(), size*sizeof(A), MPI_BYTE, pid_proc_recv, tag, comm, MPI_STATUS_IGNORE);  
    /*    ez_send(pid_proc_send, data_send, tag, comm);
	  ez_recv(pid_proc_recv, data_recv, tag, comm, status);*/
  }
};
