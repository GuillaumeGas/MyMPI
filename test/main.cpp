#include <iostream>
#include <vector>

#define __cpp98_version__

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
    int a;
    if(proto.pid == 0) {
      a = 2;
      proto.m.send(1, a);
      a = 3;
    } else {
      proto.m.recv(0, a);
    }
    test(a);
  }

  void test(int a) {
    global::barrier(MPI_COMM_WORLD);
    cout << "Je suis " << proto.pid << " : " << a << endl;
    global::barrier(MPI_COMM_WORLD);
  }
};

int main(int argc, char ** argv) {

  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
