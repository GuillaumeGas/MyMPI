#pragma once

#include <functional>

#include <mpiez/include/Globals.hpp>

namespace mpiez {
  template <typename A>
  struct Process {
    Process(A proto) : proto(proto) {
    }

    virtual void routine() = 0;
    
#if (__cplusplus >= 201103L)
    template <typename T>
    void blockExec(void (T::*fct)()) {
      global::barrier(MPI_COMM_WORLD);
      static_assert(std::is_base_of<Process,T>::value, "Error : the class of your method must inherited of Process");
      (static_cast<T*>(this)->*fct)();
      global::barrier(MPI_COMM_WORLD);
    }

    template <typename T, typename V>
    void blockExec(void (T::*fct)(V), V value) {
      global::barrier(MPI_COMM_WORLD);
      static_assert(std::is_base_of<Process,T>::value, "Error : the class of your method must inherited of Process");
      (static_cast<T*>(this)->*fct)(value);
      global::barrier(MPI_COMM_WORLD);
    }
#endif

    A proto;
    int argc;
    char** argv;
  };

};
