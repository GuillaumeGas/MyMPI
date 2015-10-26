#include <iostream>

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
    int size = 10;
    int * tab = new int[size];

    srand(time(NULL)+proto.pid);
    for(int i = 0; i < size; i++) { tab[i] = rand()%100; }

    cout << "[PREV] Je suis " << proto.pid << " : ";
    print_array(tab, size);

    execute(tab, size);

    cout << "[AFTER] Je suis " << proto.pid << " : ";
    print_array(tab, size);
  }

  void execute(int * tab, int size) {
    int next_proc = proto.pid+1;
    int prev_proc = proto.pid-1;
    if(proto.pid == 0) {
      proto.m.send_recv_replace(next_proc, next_proc, tab+(size/2), size/2);
    } else if(proto.pid == (proto.nprocs-1)) {
      proto.m.send_recv_replace(prev_proc, prev_proc, tab, size/2);
    } else {
      proto.m.send_recv_replace(next_proc, next_proc, tab+(size/2), size/2);
      proto.m.send_recv_replace(prev_proc, prev_proc, tab, size/2);
    }
  }

  void print_array(int * array, int size) {
//global::barrier(MPI_COMM_WORLD);
    for(int i = 0; i < size; i++) {
      cout << array[i] << ", ";
    }
    cout << endl;
//  global::barrier(MPI_COMM_WORLD);
  }
};

int main(int argc, char** argv) {
  Mpiez<Prot,Proc> mp(argc, argv);
  mp.finalize();
  return 0;
}
