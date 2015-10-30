#include <iostream>
#include <vector>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<int> m;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    int a[5] = {1, 2, 3, 4, 5};
    int b[10];
    proto.m.allgather(a, b, 5);
    test(b);
  }

  void test(int* a) {
    global::barrier(MPI_COMM_WORLD);
    cout << "Je suis " << proto.pid << " : ";
    for(int i = 0; i < 10; i++) { cout << a[i] << ", "; } cout << endl;
    global::barrier(MPI_COMM_WORLD);
  }
};

int main(int argc, char ** argv) {

  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
