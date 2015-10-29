#include <iostream>
#include <vector>

#include <mpiez/include/Mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<vector<int> > m;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    vector<int> a = {1, 2, 3};
    vector<int> b;
    proto.m.allgather(a, b);
    test(b);
  }

  void test(vector<int>& a) {
    global::barrier(MPI_COMM_WORLD);
    cout << "Je suis " << proto.pid << " : ";
    for(auto i : a) { cout << i << ", "; } cout << endl;
    global::barrier(MPI_COMM_WORLD);
  }
};

int main(int argc, char ** argv) {

  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
