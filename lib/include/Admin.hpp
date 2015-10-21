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
    Admin(int argc, char ** argv) {
      
      m_prot = new A(0, 1);
      m_proc = new T(*m_prot);

      m_proc->routine();
      
    }

    void finalize() {}
    
    A * m_prot;
    T * m_proc;
  };
};
