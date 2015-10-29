#include <iostream>
#include <vector>

#include <mpiez/include/Mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0, int> m;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    int a[4];
    if(proto.pid == 0) {
      for(int i=0;i<4;i++) { a[i]=i;}
      proto.m.send(1, a, 4);
      a[0]=1;
    } else {
      proto.m.recv(0, a, 4);
    }
    test(a, 4);
  }

  void test(int *a, int size) {
    global::barrier(MPI_COMM_WORLD);
    cout << "Je suis " << proto.pid << " : ";
    for(int i = 0; i < size; i++) { cout << a[i] << ", "; } cout << endl;
    global::barrier(MPI_COMM_WORLD);
  }
};

int main(int argc, char ** argv) {

  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
