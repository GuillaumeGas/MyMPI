#include <iostream>
#include <vector>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0, int> m;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}
  
  void routine() {
    int pid_prev = ((proto.pid-1)+proto.nprocs)%proto.nprocs;
    int pid_next = (proto.pid+1)%proto.nprocs;

    int size = atoi(argv[1]);

    vector<int> vec;
    srand(time(NULL)+proto.pid);
    for(int i = 0; i < size; i++ ){
      vec.push_back(rand()%size);
    }

    /*cout << "DEBUT Je suis " << proto.pid << " : ";
    for(auto i : vec) { cout << i << ", "; } cout << endl;
    */
    int* d = vec.data();
    for(int i = 0; i < vec.size(); i++) {
      proto.m.send(pid_next, *(d));
      proto.m.recv(pid_prev, *(d++));
    }

    cout << "FIN Je suis " << proto.pid << " : ";
    for(auto i : vec) { cout << i << ", "; } cout << endl;
  }
  

};

int main(int argc, char** argv) {
  Mpiez<Prot, Proc> mpi(argc, argv);
  mpi.finalize();
  return 0;
}
