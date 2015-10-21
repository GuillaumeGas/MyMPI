#include <iostream>
#include "include/Admin.hpp"
#include "include/Protocol.hpp"
#include "include/Process.hpp"
#include "include/Message.hpp"

using namespace std;
using namespace mmpi;

struct Prot : Protocol {
  Prot(int id, int nprocs) : Protocol(id, nprocs) {}
  Message<0, int> m1;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    if(proto.id == 0) {
      proto.m1.send(1, 42);
    } else {
      int a;
      proto.m1.recv(1, a);
      cout << a << endl;
    }
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
