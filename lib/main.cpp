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
  Message<3, string> m4;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    if(proto.pid == 0) {
      int a = 43;
      int tab[4] = {1, 2, 3, 4};
      char tab2[3] = {'a', 'b'};
      vector<int> vec = {1, 2, 3, 4};
      string str = "bonjour";
      
      proto.m4.send(1, str);
      
    } else {
      int b = 2;
      int t[4];
      char t2[2];
      string str;
      vector<int> vec_res;
      string res;

      proto.m4.recv(0, res);
      cout << res << endl;
    }
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
