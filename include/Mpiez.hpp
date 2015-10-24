#pragma once

#include <iostream>
#include <vector>
#include <mpi.h>

#include <mpiez/Protocol.hpp>
#include <mpiez/Process.hpp>
#include <mpiez/Globals.hpp>

using namespace std;

namespace mpiez {  
  template <typename A, typename T>
  struct Mpiez {    
    Mpiez(int argc, char ** argv) : m_prot(NULL), m_proc(NULL) {

      // try {
	if(instance == NULL) {
	  instance = this;

	  int pid, nprocs;
	  MPI_Init(&argc, &argv);
	  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
      
	  m_prot = new A(pid, nprocs);
	  m_proc = new T(*m_prot);

	  m_proc->routine(); 
	}
	  /*	} else {
	  throw MMPIInstanceException();
	}
      } catch(MMPIException const& e) {
	e.what();
	}*/
    }

    ~Mpiez() {
      if(instance == this) {
	if(m_prot)
	  delete m_prot;
	if(m_proc)
	  delete m_proc;
      }
    }

    void finalize() {
      if(instance == this) {
	global::barrier(MPI_COMM_WORLD);
	MPI_Finalize();
      }
    }
    
    A * m_prot;
    T * m_proc;
    static Admin * instance;
  };

  template<typename A, typename T>
  Admin<A,T> * Admin<A,T>::instance = NULL;
};