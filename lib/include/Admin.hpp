#pragma once

#include <iostream>
#include <vector>
#include <mpi.h>

#include "Protocol.hpp"
#include "Process.hpp"

using namespace std;

namespace mmpi {  
  template <typename A, typename T>
  struct Admin {    
    Admin(int argc, char ** argv) : m_prot(NULL), m_proc(NULL) {

      int pid, nprocs;
      MPI_Init(&argc, &argv);
      MPI_Comm_rank(MPI_COMM_WORLD, &pid);
      MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
      MPI_Status status;
      
      m_prot = new A(pid, nprocs);
      m_proc = new T(*m_prot);

      m_proc->routine();
      
    }

    ~Admin() {
      if(m_prot)
	delete m_prot;
      if(m_proc)
	delete m_proc;
    }

    void finalize() {
      MPI_Barrier(MPI_COMM_WORLD);
      MPI_Finalize();
    }
    
    A * m_prot;
    T * m_proc;
  };
};
