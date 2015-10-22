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
  Message<4, string, int> m5;
  Message<5, int> m6;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    if(proto.pid == 0) {
      int a = 2;
      proto.m1.ssend(1, a);
    } else {
      int a;
      proto.m1.recv(0, a);
      cout << "a : " << a << endl;
    }

    /*if(proto.pid == 0) {
      int a = -1;
      string n = "serge";
      string n2;
      proto.m6.send_recv(1, 1, proto.pid, a);
      cout << "Je suis " << n << " le process " << proto.pid << ", " << n2 << ": " << a << endl;
    } else {
      int a = -1;
      string n = "francois";
      string n2;
      proto.m6.send_recv(0, 0, proto.pid, a);
      cout << "Je suis " << n << " le process " << proto.pid << ", " << n2 << ": " << a << endl;
      }*/
    /*if(proto.pid == 0) {
      int a = 43;
      int b;
      int tab[4] = {1, 2, 3, 4};
      char tab2[3] = {'a', 'b'};
      vector<int> vec = {1, 2, 3, 4};
      string str = "emile";
      
      proto.m6.send_recv(0, 1, a, b);
      cout << "Je suis " << proto.pid << ", res = " << b << endl;
      
    } else {
      int b = 2;
      int a;
      int t[4];
      char t2[2];
      string str;
      vector<int> vec_res;
      string res;

      proto.m6.send_recv(0, res, b);
      cout << res << " a " << b << " ans." << endl;
      }*/
  }
};

int main(int argc, char ** argv) {

  Admin<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
