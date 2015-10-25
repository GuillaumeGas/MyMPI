# MPIEZ #

The main goal of this C++ library is to allow to use the MPI library easily. 

### Example ###


```
#!C++

#include <iostream>
#include <vector>

#include <mpiez/include/Mpiez.hpp>

using namespace std;
using namespace mpiez;

//(1) We create a protocol with our "messages"
struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0, int> m;
};

//(2) We create a process with our protocol and we override the "routine" method
struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    int a;
    if(proto.pid == 0) {
      a = 2;
      proto.m.send(1, a); //we send an int to process 1
      a = 3;
    } else {
      proto.m.recv(0, a); //we receive an int from process 0
    }
    cout << "I am " << proto.pid << " a = " << a << endl; 
    /* Result:
    I am 0 a = 3
    I am 1 a = 2
    */
  }
};

int main(int argc, char ** argv) {

  Mpiez<Prot, Proc> ad(argc, argv); //we create a mpiez object in which mpi is initialized
  ad.finalize();
  
  return 0;
}
```


### What can you do whith MPIEZ ###

1 dim : MPI_COMM_WORLD

# Point to point communications
* send
* ssend
* bsend
* send_recv
* send_recv_replace

# Collective communications
* bcast
* scatter
* gather

Type of data allowed : int, char, string, vector<int>, vector<char>
If you want to use int* or char*, you have to add the following define before including Mpiez.hpp : 

```
#!C++

#define __cpp98_version__ 
```


[!] : if you use this define, you can't use the vector type anymore.

# Point to point communications
* MPI_Sendrecv_replace (STRING)
* MPI_Isend
* MPI_Irecv
* MPI_Issend
* MPI_Ibsend

# Collective communications
* MPI_Allgather
* MPI_Alltoall
* MPI_Reduce
* MPI_Allreduce
* MPI_Scatterv
* MPI_Gatherv
* MPI_Allgatherv
* MPI_Alltoallv

# Global methods
* MPI_Test        //we should use it if Irecv returns a *request
* MPI_Testall
* MPI_Testany
* MPI_Wait
* MPI_Waitall
* MPI_Waitany

# Communicators
*MPI_Comm_split
*MPI_Comm_rank
*MPI_Cart_create
*MPI_Cart_rank
*MPI_Cart_coord
*MPI_Cart_shift
*MPI_Cart_get
*MPI_Cartdim_get
*MPI_Cart_sub