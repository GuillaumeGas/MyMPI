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
    /*if(proto.pid == 0) {
      vector<int> a = {1, 2, 3, 4};
      proto.m3.ssend(1, a);
      for(auto i : a) { cout << i; } cout << endl;
      } else {
      vector<int> a;
      proto.m3.recv(0, a);
      for(auto i : a) { cout << i; } cout << endl;
      }*/

    if(proto.pid == 0) {
      //      vector<int> a = {1, 2, 3};
      //      vector<int> b;
      //      b.resize(a.size());
      string c = "test";
      string d;
      //      proto.m3.send_recv(1, 1, a, b);
      proto.m4.send_recv(1, 1, c, d);
      cout << "Je suis le process " << proto.pid << " : " << endl;
      cout << "(" << proto.pid << ") " << "Chaine : " << d << endl;
      //      for(auto i : b) {cout << i;} cout << endl;
    } else {
      //      vector<int> a = {4, 5, 6};
      //      vector<int> b;
      //      b.resize(a.size());
      string c = "bidul";
      string d;
      //proto.m3.send_recv(0, 0, a, b);
      proto.m4.send_recv(0, 0, c, d);
      cout << "Je suis le process " << proto.pid << " : " << endl;
      cout << "(" << proto.pid << ") " << "Chaine : " << d << endl;
      //      for(auto i : b) {cout << i;} cout << endl;
    }
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
