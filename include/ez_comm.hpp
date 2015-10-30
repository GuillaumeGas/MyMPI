#pragma once

#include <mpi.h>

namespace mpiez {
  namespace comm {
    void split(MPI_Comm& comm_old, int color, int key, MPI_Comm* comm_new) {
      MPI_Comm_split(comm_old, color, key, comm_new);
    }

    void rank(MPI_Comm& comm, int* pid) {
      MPI_Comm_rank(comm, pid);
    }

    void cart_rank(MPI_Comm& comm, int* coords, int* rank) {
      MPI_Cart_rank(comm, coords, rank);
    }

    void cart_create(MPI_Comm& comm_old, int ndims, int* dims, int* periods, int reorder, MPI_Comm* comm_new) {
      MPI_Cart_create(comm_old, ndims, dims, periods, reorder, comm_new);
    }

    void dims_create(int nnodes, int ndims, int* dims) {
      MPI_Dims_create(nnodes, ndims, dims);
    }

    void cart_coords(MPI_Comm& comm, int rank, int maxdims, int* coords) {
      MPI_Cart_coords(comm, rank, maxdims, coords);
    }

    void cart_shift(MPI_Comm& comm, int direction, int displ, int* source, int* dest) {
      MPI_Cart_shift(comm, direction, displ, source, dest);
    }

    void cart_get(MPI_Comm& comm, int maxdims, int* dims, int* periods, int* coords) {
      MPI_Cart_get(comm, maxdims, dims, periods, coords);
    }

    void cartdim_get(MPI_Comm& comm, int* ndims) {
      MPI_Cartdim_get(comm, ndims);
    }

    void cart_sub(MPI_Comm& comm, int* remain_dims, MPI_Comm* comm_new) {
      MPI_Cart_sub(comm, remain_dims, comm_new);
    }
  };
};
