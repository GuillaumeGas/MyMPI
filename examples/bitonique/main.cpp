#include <iostream>
#include <vector>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<vector<int> > cm;
  Message<0, int> pm;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    vector<int> big_array = {2, 3, 4, 5, 6, 8, 10, 7, 1};
    vector<int> local_array;

    int big_array_size = big_array.size();

    proto.cm.scatter(0, big_array, local_array, big_array_size);
    global::syncExec(this, &Proc::print_vec, local_array);

    int next_proc = (proto.pid+1)%proto.nprocs;
    int prev_proc = ((proto.pid-1)+proto.nprocs)%proto.nprocs;
    int val;
    proto.pm.send_recv(next_proc, prev_proc, local_array[local_array.size()-1], val);
    local_array.insert(local_array.begin(), val);

    global::syncExec(this, &Proc::print_vec, local_array);
  }

  void print_vec(vector<int> vec) {
    cout << "Je suis " << proto.pid << " : ";
    for(auto i : vec) { cout << i << ", "; } cout << endl;
  }
};

int main(int argc, char** argv) {
  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  return 0;
}
