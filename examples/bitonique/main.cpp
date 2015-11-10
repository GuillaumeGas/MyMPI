#include <iostream>
#include <vector>
#include <algorithm>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<vector<int> > cm;
  ColMessage<int> cm2;
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

    int res = testBitoniqueSimpleLocal(local_array);

    global::syncExec(this, &Proc::print_vec, local_array);
    global::syncExec(this, &Proc::print_res, res);

    vector<int> tab_res;
    tab_res.resize(proto.nprocs);
    proto.cm2.gather(0, &res, tab_res.data(), proto.nprocs);

    int global_res = -2;
    if(proto.pid == 0) {
      print_ress(tab_res);
      auto it = find(tab_res.begin(), tab_res.end(), 0);
      if(it != tab_res.end()) {
	global_res = testBitoniqueSimpleLocal(tab_res);
      } else {
	global_res = -2;
      }
      cout << "glob res = " << global_res << endl;
    }
    
    proto.cm2.bcast(0, &global_res, 1);

    
   
  }

  int testBitoniqueSimpleLocal(vector<int> vec) {
    int res = -3;
    for(int i = 1; i < vec.size(); i++) {
      if(vec[i] > vec[i-1] && (res == 0 || res == -1)) {
	return -2;
      } else if(vec[i] < vec[i-1] && res == -3) {
	res = -1;
      } else if(vec[i] > vec[i-1] && res == -3) {
	res = 1;
      } else if(vec[i] < vec[i-1] && res == 1) {
	res = 0;
      } else if(vec[i] == vec[i-1] && res == -3) {
	res = 1;
      }
    }
    return res;
  }
  
  void print_vec(vector<int> vec) {
    cout << "Je suis " << proto.pid << " : ";
    for(auto i : vec) { cout << i << ", "; } cout << endl;
  }

  void print_res(int n) {
    cout << "Je suis " << proto.pid << " : res = " << n << endl;
  }

  void print_ress(vector<int> res) {
    cout << "results : ";
    for(auto i : res) { cout << i << ", "; } cout << endl;
  }
};

int main(int argc, char** argv) {
  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  return 0;
}
