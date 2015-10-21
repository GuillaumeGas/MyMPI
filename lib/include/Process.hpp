#pragma once

namespace mmpi {
  template <typename A>
  struct Process {
    Process(A proto) : proto(proto) {
    }

    virtual void routine() = 0;
    
    A proto;
  };
};
