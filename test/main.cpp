#include <iostream>
#include <vector>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0,int> m;
};

struct Proc : Process<Prot> {
  Proc(Prot & p, int argc, char** argv) : Process(p, argc, argv) {}

  void routine() {
    MPI_Request r1, r2;
    MPI_Status s1,s2;

    int a = 0;
    if(proto.pid == 0) {
      a = 1;
      proto.m.ibsend(1,&a,1,&r1);
      global::wait(&r1,&s1);
      a = 2;
    } else {
      proto.m.irecv(0,a,&r2);
      global::wait(&r2,&s2);
    }

   
    cout << "Je suis " << proto.pid << " : " << a << endl;
  }

};

int main(int argc, char ** argv) {
  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  return 0;
}
