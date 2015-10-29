#pragma once

#include <mpi.h>
#include <vector>

namespace mpiez {
  template<typename A>
  void ez_bcast(int root_pid, std::vector<A>& buffer, MPI_Comm comm) {
    MPI_Bcast(buffer.data(), buffer.size()*sizeof(A), MPI_BYTE, root_pid, comm);
  }

  template<typename A>
  void ez_scatter(int root_pid, std::vector<A>& send_buffer, std::vector<A>& recv_buffer, int tot_size, int nprocs, MPI_Comm comm) {
    if(tot_size%nprocs != 0) {
      //TODOO EXCEPTION
      throw "Size is not divisible by number of process !";
    } else {
      int size = tot_size/nprocs;
      recv_buffer.resize(size);
      MPI_Scatter(send_buffer.data(), size*sizeof(A), MPI_BYTE, recv_buffer.data(), size*sizeof(A), MPI_BYTE, root_pid, comm);
    }
  }

  template<typename A>
  void ez_scatterv(int root_pid, std::vector<A>& send_buffer, std::vector<A>& recv_buffer, int tot_size, int pid, int nprocs, MPI_Comm comm) {
    int n_local = tot_size/nprocs;
    int nprocs_left = tot_size%nprocs;
    int recv_size = n_local;

    int* counts = NULL;
    int* displs = NULL;
    
    if(pid == root_pid) {
      counts = new int[nprocs];
      displs = new int[nprocs];

      int ptr = 0;
      for(int i = 0; i < nprocs_left; i++) {
	counts[i] = (n_local+1)*sizeof(A);
	displs[i] = ptr;
	ptr += (n_local+1)*sizeof(A);
      }
      for(int i = nprocs_left; i < nprocs; i++) {
	counts[i] = n_local*sizeof(A);
	displs[i] = ptr;
	ptr += n_local*sizeof(A);
      }

    }
    if(pid < nprocs_left)
      recv_size += 1;
    recv_buffer.resize(recv_size);
    MPI_Scatterv(send_buffer.data(), counts, displs, MPI_BYTE, recv_buffer.data(), recv_size*sizeof(A), MPI_BYTE, root_pid, comm); 
    delete[] counts;
    delete[] displs;
  }

  template <typename A>
  void ez_gather(int root_pid, std::vector<A>& send_buffer, std::vector<A>& recv_buffer, int pid, int nprocs, MPI_Comm comm) {
    if(pid == root_pid && recv_buffer.size() < (send_buffer.size()*nprocs)) {
      recv_buffer.resize(send_buffer.size()*nprocs);
    } else {
      MPI_Gather(send_buffer.data(), send_buffer.size()*sizeof(A), MPI_BYTE, recv_buffer.data(), send_buffer.size()*sizeof(A), MPI_BYTE, root_pid, comm); 
    }
  }

  template<typename A>
  void ez_gatherv(int root_pid, std::vector<A>& send_buffer, std::vector<A>& recv_buffer, int tot_size, int pid, int nprocs, MPI_Comm comm) {
    int n_local = tot_size/nprocs;
    int nprocs_left = tot_size%nprocs;
    int send_size = n_local;

    if(pid == root_pid && recv_buffer.size() < tot_size) {
      recv_buffer.resize(tot_size+1);
    }

    int* counts = NULL; 
    int* displs = NULL;

    if(pid == root_pid) {
      counts = new int[nprocs];
      displs = new int[nprocs];
      int ptr = 0;
      for(int i = 0; i < nprocs_left; i++) {
	counts[i] = (n_local+1)*sizeof(A);
	displs[i] = ptr;
	ptr += (n_local+1)*sizeof(A);
      }
      for(int i = nprocs_left; i < nprocs; i++) {
	counts[i] = n_local*sizeof(A);
	displs[i] = ptr;
	ptr += n_local*sizeof(A);
      }
    }
    if(pid < nprocs_left)
      send_size += 1;
    
    MPI_Gatherv(send_buffer.data(), send_size*sizeof(A), MPI_BYTE, recv_buffer.data(), counts, displs, MPI_BYTE, root_pid, comm); 
    delete[] counts;
    delete[] displs;
  }
};
