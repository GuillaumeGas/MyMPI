#pragma once

#include <mpi.h>
#include <string>

#include <mpiez/include/ez_base.hpp>

using namespace std;

namespace mpiez {
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

  void ez_bsend(int pid_proc, string& str, int tag, MPI_Comm comm) {
    int str_size = str.size();
    int size;
    MPI_Pack_size(str_size, MPI_BYTE, comm, &size);
    size += MPI_BSEND_OVERHEAD;
    char* buffer = new char[size];
    char* c_str = new char[str_size+1];
    for(int i = 0; i < str_size; i++) {
      c_str[i] = str[i];
    }
    c_str[str_size] = '\0';
    MPI_Buffer_attach(buffer, size);
    MPI_Bsend(c_str, str_size+1, MPI_BYTE, pid_proc, tag, comm);
    MPI_Buffer_detach(c_str, &size);
    delete[] buffer;
    delete[] c_str;
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

  void ez_send_recv(int pid_proc_send, int pid_proc_recv, string& data_send, string& data_recv, int tag, MPI_Comm comm, MPI_Status& status) {
    ez_send(pid_proc_send, data_send, tag, comm);
    ez_recv(pid_proc_recv, data_recv, tag, comm, status);
  }

};
