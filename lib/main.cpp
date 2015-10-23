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
    if(proto.pid == 0) {
      vector<int> a = {1, 2, 3};
      proto.m2.send_recv_replace(1, 1, a);
      cout << "Je suis " << proto.pid << " : ";
      for(auto i : a) { cout << i; } cout << endl;
    } else {
      vector<int> a = {4, 5, 6};
      proto.m2.send_recv_replace(0, 0, a);
      cout << "Je suis " << proto.pid << " : ";
      for(auto i : a) { cout << i; } cout << endl;
    }
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
