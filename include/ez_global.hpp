#pragma once

#include <mpi.h>

namespace mpiez {
  namespace global {
    void barrier(MPI_Comm comm) {
      MPI_Barrier(comm);
    }

    void test(MPI_Request* req, int* flag, MPI_Status* status) {
      MPI_Test(req, flag, status);
    }

    void test_any(int count, MPI_Request* array_of_req, int* index, int* flag, MPI_Status* status) {
      MPI_Testany(count, array_of_req, index, flag, status);
    }

    void test_all(int count, MPI_Request* array_of_req, int* flag, MPI_Status* array_of_status) {
      MPI_Testall(count, array_of_req, flag, array_of_status);
    }

    void wait(MPI_Request* request, MPI_Status* status) {
      MPI_Wait(request, status);
    }

    void wait_any(int count, MPI_Request* array_of_req, int* index, MPI_Status* status) {
      MPI_Waitany(count, array_of_req, index, status);
    }

    void wait_all(int count, MPI_Request* array_of_req, MPI_Status* array_of_status) {
      MPI_Waitall(count, array_of_req, array_of_status);
    }
};
