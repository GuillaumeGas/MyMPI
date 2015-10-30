#pragma once

namespace mpiez {
  struct Protocol {
    Protocol(int pid, int nprocs) : pid(pid), nprocs(nprocs) {}
    
    int pid;
    int nprocs;
  };
};
