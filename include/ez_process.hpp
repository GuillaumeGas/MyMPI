#pragma once

#include <mpiez/include/ez_global.hpp>

namespace mpiez {
  template <typename A>
  struct Process {
    Process(A proto, int argc = 0, char** argv = NULL) : proto(proto), argc(argc), argv(argv) {}

    virtual void routine() = 0;

    A proto;
    int argc;
    char** argv;
  };
};
