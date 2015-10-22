#pragma once

#include <mpi.h>
#include <string>
#include "ez_base.hpp"

using namespace std;

namespace mmpi {
  void ez_send(int pid_proc, string& str, int tag, MPI_Comm comm) {
    int size = str.size();
    char * c_str = new char[size+1];
    for(int i = 0; i < size; i++) {
      c_str[i] = str[i];
    }
    c_str[size] = '\0';
    MPI_Send(c_str, size+1, MPI_BYTE, pid_proc, tag, comm);
  }

  void ez_ssend(int pid_proc, string& str, int tag, MPI_Comm comm) {
    int size = str.size();
    char * c_str = new char[size+1];
    for(int i = 0; i < size; i++) {
      c_str[i] = str[i];
    }
    c_str[size] = '\0';
    MPI_Ssend(c_str, size+1, MPI_BYTE, pid_proc, tag, comm);
  }

  void ez_recv(int pid_proc, string& str, int tag, MPI_Comm comm, MPI_Status& status) {
    int size;
    MPI_Probe(pid_proc, tag, comm, &status);
    MPI_Get_count(&status, MPI_BYTE, &size);
    char * data = new char[size];
    MPI_Recv(data, size, MPI_BYTE, pid_proc, tag, comm, MPI_STATUS_IGNORE);
    str = data;
    delete[] data;
  }
};
