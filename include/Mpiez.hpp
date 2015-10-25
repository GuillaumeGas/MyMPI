#pragma once

#include <iostream>
#include <vector>
#include <mpi.h>

#include <mpiez/include/Protocol.hpp>
#include <mpiez/include/Process.hpp>
#include <mpiez/include/Globals.hpp>
#if (__cplusplus < 201103L) || defined(__cpp98_version__)
#include <mpiez/include/Message_cpp98.hpp>
#else
#include <mpiez/include/Message.hpp>
#endif
#include <mpiez/include/CollectiveMessage.hpp>

using namespace std;

namespace mpiez {  
  template <typename A, typename T>
  struct Mpiez {    
    Mpiez(int argc, char ** argv) : m_prot(NULL), m_proc(NULL) {

      if(instance == NULL) {
	instance = this;

	int pid, nprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
      
	m_prot = new A(pid, nprocs);
	m_proc = new T(*m_prot);
	m_proc->argc = argc;
	m_proc->argv = argv;

	m_proc->routine(); 
      }
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
    static Mpiez * instance;
  };

  template<typename A, typename T>
  Mpiez<A,T> * Mpiez<A,T>::instance = NULL;
};
