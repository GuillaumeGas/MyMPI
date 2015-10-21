#include <iostream>
#include "include/Admin.hpp"
#include "include/Protocol.hpp"
#include "include/Process.hpp"
#include "include/Message.hpp"

using namespace std;
using namespace mmpi;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0, int> m1;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    if(proto.pid == 0) {
      int tab[4] = {1, 2, 3, 4};
      //      cout << "tialle" << sizeof(tab) << endl;
      int a = 43;
      proto.m1.send_array(1, tab, 4);
      for(int i = 0; i < 4; i++) {
	cout << tab[i] << endl;
      }
      //cout << "Envoie : " << a << endl;
    } else {
      int b = 2;
      int t[4];
      proto.m1.recv_array(0, t, 4);
      //      cout << "Reception : " << b << endl;
      for(int i = 0; i < 4; i++) {
	cout << t[i] << endl;
      }
    }
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
