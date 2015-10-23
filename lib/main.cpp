#include <iostream>
#include <vector>
#include "include/Admin.hpp"
#include "include/Protocol.hpp"
#include "include/Process.hpp"
#include "include/Message.hpp"
#include "include/CollectiveMessage.hpp"

using namespace std;
using namespace mmpi;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0, int> m1;
  Message<1, vector<int> > m2;
  Message<2, string> m3;

  ColMessage<int> m4;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    int a = -1;
    if(proto.pid == 0) {
      a = 2;
    }
    proto.m4.bcast(0, a);
    cout << "Je suis " << proto.pid << " : " << a << endl;
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
