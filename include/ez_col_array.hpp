#pragma once
namespace mpiez {
  template<typename A>
  void ez_bcast(int root_pid, A* buffer, int size, MPI_Comm comm) {
    MPI_Bcast(buffer, size*sizeof(A), MPI_BYTE, root_pid, comm);
  }

  template<typename A>
  void ez_scatter(int root_pid, A* send_buffer, A* recv_buffer, int tot_size, int nprocs, MPI_Comm comm) {
    if(tot_size%nprocs != 0) {
      //TODOO EXCEPTION
      throw "Size is not divisible by number of process ! You should use scatterv instead.";
    } else {
      int size = tot_size/nprocs;
      MPI_Scatter(send_buffer, size*sizeof(A), MPI_BYTE, recv_buffer, size*sizeof(A), MPI_BYTE, root_pid, comm);
    }
  }

  template<typename A>
  void ez_scatterv(int root_pid, A* send_buffer, A* recv_buffer, int tot_size, int pid, int nprocs, MPI_Comm comm) {
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
    MPI_Scatterv(send_buffer, counts, displs, MPI_BYTE, recv_buffer, recv_size*sizeof(A), MPI_BYTE, root_pid, comm); 
  }

  template <typename A>
  void ez_gather(int root_pid, A* send_buffer, A* recv_buffer, int tot_size, int nprocs, MPI_Comm comm) {
    int size = tot_size/nprocs;
    MPI_Gather(send_buffer, size*sizeof(A), MPI_BYTE, recv_buffer, size*sizeof(A), MPI_BYTE, root_pid, comm); 
  }

  template<typename A>
  void ez_gatherv(int root_pid, A* send_buffer, A* recv_buffer, int tot_size, int pid, int nprocs, MPI_Comm comm) {
    int n_local = tot_size/nprocs;
    int nprocs_left = tot_size%nprocs;
    int send_size = n_local;

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
    
    MPI_Gatherv(send_buffer, send_size*sizeof(A), MPI_BYTE, recv_buffer, counts, displs, MPI_BYTE, root_pid, comm); 
  }
};
