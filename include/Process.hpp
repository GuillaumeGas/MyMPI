#pragma once

#include <mpiez/include/Globals.hpp>

namespace mpiez {
  template <typename A>
  struct Process {
    Process(A proto) : proto(proto) {
    }

    virtual void routine() = 0;
    
    /*    template <typename T>
    blockExec(void (*fct)(T), T value) {
      global::barrier(MPI_COMM_WORLD);
      (*fct)(value);
      global::barrier(MPI_COMM_WORLD);
      }*/

    A proto;
    int argc;
    char** argv;
  };

};
