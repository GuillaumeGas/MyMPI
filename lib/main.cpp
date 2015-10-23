#include <iostream>
#include <vector>
#include "include/Admin.hpp"
#include "include/Protocol.hpp"
#include "include/Process.hpp"
#include "include/Message.hpp"

using namespace std;
using namespace mmpi;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0, int> m1;
  Message<1, vector<int> > m2;
  Message<2, string> m3;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    string a;
    if(proto.pid == 0) {
      a = "test";
      proto.m3.bsend(1, a);
    } else {
      proto.m3.recv(0, a);
      cout << "je suis : " << proto.pid << endl;
      cout << "res : " << a << endl;
    }
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
