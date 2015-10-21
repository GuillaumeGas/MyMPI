#pragma once

namespace mmpi {
  struct Protocol {
    Protocol(int id, int nprocs) : id(id), nprocs(nprocs) {}
    
    int id;
    int nprocs;
  };
};
