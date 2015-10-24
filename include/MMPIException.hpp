#pragma once

namespace mpiez {
  class MMPIException {
  public:
    MMPIException() {}
    virtual void what() const {}
  };

  class MMPIInstanceException : MMPIException {
  public:
    MMPIInstanceException() {}
    void what() const {
      std::cout << "Only one instance of Admin class is allowed." << std::endl;
    }
  };
};
