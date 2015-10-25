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
      int b[4] = {1, 2, 3, 4};
      proto.m.send(1, b, 4);
    } else {
      proto.m.recv(0, a, 4);
    }
    cout << "Je suis " << proto.pid << " : ";
    for(int i = 0;i<4;i++) {cout<<a[i];}cout<<endl;
  }
};

int main(int argc, char ** argv) {

  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
