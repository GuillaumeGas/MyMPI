#pragma once

#include <mpiez/include/ez_global.hpp>

namespace mpiez {
  template <typename A>
  struct Process {
    Process(A proto) : proto(proto) {}

    virtual void routine() = 0;

    A proto;
    int argc;
    char** argv;
  };
};
