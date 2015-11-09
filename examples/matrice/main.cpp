#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cmath>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0,int> m;
};

struct Proc : Process<Prot> {
  MPI_Comm Default_comm;
  MPI_Comm Comm_grille;
  int n;
  int ndims, periods[2], dims[2];
  bool reorder;
  int coords[2];

  int *A_local, *B_local, *C_local;

  Proc(Prot & p, int argc, char** argv) : Process(p, argc, argv) {
    n = atoi(argv[1]);
    ndims = 2;
    reorder = true;
    periods[0] = periods[1] = 1;
    dims[0]    = dims[1]    = 0; 
    Default_comm = MPI_COMM_WORLD;

    comm::dims_create(proto.nprocs, ndims, dims);
    comm::cart_create(Default_comm, ndims, dims, periods, reorder, &Comm_grille);
    proto.m.set_comm(Comm_grille);
    comm::cart_coords(Comm_grille, proto.pid, ndims, coords);

    srand(proto.pid);

    init_mats();
  }

  ~Proc() {
    if(A_local)
      delete[] A_local;
    if(B_local)
      delete[] B_local;
    if(C_local)
      delete[] C_local;
  }

  void routine() {

    int tours = sqrt(proto.nprocs);

    global::syncExec(this, &Proc::afficher_mat, A_local);
    global::syncExec(this, &Proc::afficher_mat, B_local);

    shift_init();

    MPI_Request reqSA, reqSB, reqRA, reqRB;
    MPI_Status status;
    
    for(int i = 0; i < tours; i++) {
      operation_elementaire(n, A_local, B_local, C_local);
      ishift(reqSA, reqSB, reqRA, reqRB);
    }

    global::syncExec(this, &Proc::afficher_mat, C_local);
    
  } 


  void shift_init() {
    int gd[2]; //gauche droite
    int hb[2]; //haut bas
    comm::cart_shift(Comm_grille, 0, -coords[1], &hb[1], &hb[0]);
    comm::cart_shift(Comm_grille, 1, -coords[0], &gd[1], &gd[0]);
    proto.m.send_recv_replace(gd[0], gd[1], A_local, n*n);
    proto.m.send_recv_replace(hb[0], hb[1], B_local, n*n);
  }


  void shift() {
    int gd[2]; //gauche droite
    int hb[2]; //haut bas
    comm::cart_shift(Comm_grille, 0, -1, &hb[1], &hb[0]);
    comm::cart_shift(Comm_grille, 1, -1, &gd[1], &gd[0]);
    proto.m.send_recv_replace(gd[0], gd[1], A_local, n*n);
    proto.m.send_recv_replace(hb[0], hb[1], B_local, n*n);
  }

  void ishift(MPI_Request& reqSA, MPI_Request& reqSB, MPI_Request& reqRA, MPI_Request& reqRB) {
    int gd[2]; //gauche droite
    int hb[2]; //haut bas
    comm::cart_shift(Comm_grille, 0, -1, &hb[1], &hb[0]);
    comm::cart_shift(Comm_grille, 1, -1, &gd[1], &gd[0]);

    int* a_tmp = new int[n*n];
    int* b_tmp = new int[n*n];

    proto.m.issend(gd[0], A_local, n*n, &reqSA);
    proto.m.irecv(gd[1], a_tmp, n*n, &reqRA);

    proto.m.issend(hb[0], B_local, n*n, &reqSB);
    proto.m.irecv(hb[1], b_tmp, n*n, &reqRB);
    
    global::wait(&reqRA, &status);
    global::wait(&reqRB, &status);

    delete[] A_local;
    delete[] B_local;
    A_local = a_tmp;
    B_local = b_tmp;
  }

  void afficher_mat(int* mat) {
    cout << "Proc " << proto.pid << " : " << endl;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
	cout << mat[i*n+j] << " ";
      }
      cout << endl;
    }
    cout << endl;
    if(proto.pid == proto.nprocs-1) {
      cout << "#################################################" << endl;
    }
  }

  
  void init_mats() {
    A_local = generation_mat(n);
    B_local = generation_mat(n);
    C_local = new int[n*n];
    for(int i = 0; i < n*n; i++) { C_local[i] = 0; }
  }

  int* generation_mat(int taille) {
    int* mat = new int[taille*taille];
    for(int i = 0; i < taille*taille; i++) {
      mat[i] = rand()%10;
    }
    return mat;
  }

  void operation_elementaire(int n, int* A, int* B, int* C) {
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
	int ele = 0; 
	for (int k=0; k<n; k++)
	  ele = ele + A[i*n+k]*B[k*n+j];
	C[i*n+j] = C[i*n+j] + ele;      
      }
    }  
  }
  
};

int main(int argc, char** argv) {
  Mpiez<Prot,Proc> mp(argc, argv);
  mp.finalize();
  return 0;
}
