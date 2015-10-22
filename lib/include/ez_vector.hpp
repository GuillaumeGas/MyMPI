#pragma once

#include <mpi.h>
#include <vector>

namespace mmpi {
  template<typename A>
  void ez_send(int pid_proc, std::vector<A>& data, int tag, MPI_Comm comm) {
    MPI_Send(data.data(), data.size()*sizeof(A), MPI_BYTE, pid_proc, tag, comm);
  }

  template<typename A>
  void ez_recv(int pid_proc, std::vector<A>& data, int tag, MPI_Comm comm, MPI_Status& status) {
    int size;
    MPI_Probe(pid_proc, tag, comm, &status);
    MPI_Get_count(&status, MPI_BYTE, &size);
    cout << "size : " << size << endl;
    data.resize(size/sizeof(A));
    MPI_Recv(data.data(), size, MPI_BYTE, pid_proc, tag, comm, MPI_STATUS_IGNORE);
  }
};
