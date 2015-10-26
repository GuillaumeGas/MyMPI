#include <iostream>
#include <vector>

#include <mpiez/include/Mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  Message<0, vector<int> > m;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}
  
  void routine() {
    vector<int> vec;
    vector<int> max;
    int root = 0;

    int size = atoi(argv[1]);

    srand(time(NULL)+proto.pid);
    for(int i = 0; i < size; i++) {
      vec.push_back(rand()%(size*10));
    }

    max = {-1, -1};
    for(int i = 0; i < vec.size(); i++) {
      if(max[1] < vec[i]) {
	max[0] = i;
	max[1] = vec[i];
      }
    }

    cout << "Je suis " << proto.pid << " : ";
    for(auto i : vec) { cout << i << ", "; } cout << endl;

    if(proto.pid != root) {
      proto.m.send(root, max);
    } else {
      for(int i = 0; i < proto.nprocs; i++) {
	if(i != root) {
	  vector<int> tmp;
	  proto.m.recv(i, tmp);
	  if(tmp[1] > max[1]) {
	    max = tmp;
	  }
	}
      }
      cout << "Je suis " << proto.pid << ", max = " << max[1] << endl;
    }
  }


};

int main(int argc, char** argv) {
  Mpiez<Prot, Proc> mpi(argc, argv);
  mpi.finalize();
  return 0;
}
