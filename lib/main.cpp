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

  ColMessage<vector<int> > m4;
  ColMessage<int> m5;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    vector<int> a;
    a.resize(2);
    if(proto.pid == 0) {
      a = {1, 2};
    }
    proto.m4.bcast(0, a);
    cout << "Je suis " << proto.pid << " : " << endl;
    for(auto i : a) { cout << i; } cout << endl;
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  Admin<Prot, Proc> ad2(argc, argv);
  ad.finalize();
  ad2.finalize();
  
  return 0;
}
