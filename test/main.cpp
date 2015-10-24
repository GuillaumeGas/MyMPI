#include <iostream>
#include <vector>

#include <mpiez/include/Mpiez.hpp>
#include <mpiez/include/Protocol.hpp>
#include <mpiez/include/Process.hpp>
#include <mpiez/include/Message.hpp>
#include <mpiez/include/CollectiveMessage.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<vector<int> > m;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    vector<int> a;
    vector<int> b;
    if(proto.pid == 0) {
      for(int i = 0; i < 15; i++ ){
	a.push_back(i);
      }
    }
    proto.m.scatter(0, a, b, 5);

    cout << "Je suis " << proto.pid << " : ";
    for(auto i : b) { cout << i << ", "; } cout << endl;
    a.clear();
    a.resize(15);

    proto.m.gather(0, b, a);

    if(proto.pid == 0) {
      cout << "Je suis " << proto.pid << " : ";
      if(proto.pid == 0) {
	for(auto i : a) { cout << i << ", "; } cout << endl;
      }
    }
  }
};

int main(int argc, char ** argv) {

  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  
  return 0;
}
