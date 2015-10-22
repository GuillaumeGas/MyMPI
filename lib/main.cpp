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
  Message<1, char> m2;
  Message<2, vector<int> > m3;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    if(proto.pid == 0) {
      int a = 43;
      int tab[4] = {1, 2, 3, 4};
      char tab2[3] = {'a', 'b'};
      vector<int> vec = {1, 2, 3, 4};
      
      proto.m1.send(1, a).send(1, a);
      
    } else {
      int b = 2;
      int t[4];
      char t2[2];
      string str;
      vector<int> vec_res;

      int a,c;
      proto.m1.recv(0,a).recv(0,c);
      cout << "a = " << a <<", c= " << c << endl;
    }
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
