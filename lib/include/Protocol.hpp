#pragma once

namespace mmpi {
  struct Protocol {
    Protocol(int pid, int nprocs) : pid(pid), nprocs(nprocs) {}
    
    int pid;
    int nprocs;
  };
};
