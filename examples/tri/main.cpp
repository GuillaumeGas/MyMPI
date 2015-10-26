#include <iostream>
#include <vector>
#include <algorithm>

#include <mpiez/include/Mpiez.hpp>

#define LOCAL_SIZE 5

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<vector<int> > m;
  Message<0, vector<int> > m1;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}
  
  void routine() {
    srand(proto.pid);
    vector<int> tab;
    vector<int> tab_loc;
    
    if(proto.pid == 0) {
      for(int i = 0; i < (LOCAL_SIZE*proto.nprocs); i++) {
	tab.push_back(rand()%100);
      }
      print_vector(tab);
    }
    proto.m.scatter(0, tab, tab_loc, LOCAL_SIZE);

    sort(tab_loc.begin(), tab_loc.end());
    
    int proc_next = proto.pid+1;
    int proc_prev = proto.pid-1;
      
    for(int i = 0; i < proto.nprocs; i++) {
      vector<int> tmp;
      if(i%2 == 0) {
	if(proto.pid%2 == 0 && proc_next < proto.nprocs) {
	  proto.m1.send_recv(proc_next, proc_next, tab_loc, tmp);
	  fusion_plus_petits(tab_loc, tmp);
	} else if(proto.pid%2 != 0) {
	  proto.m1.send_recv(proc_prev, proc_prev, tab_loc, tmp);
	  fusion_plus_grands(tab_loc, tmp);
	}
      } else {
	if(proto.pid%2 == 0 && proto.pid != 0) {
	  proto.m1.send_recv(proc_prev, proc_prev, tab_loc, tmp);
	  fusion_plus_grands(tab_loc, tmp);
	} else if(proto.pid%2 != 0 && proc_next < proto.nprocs){
	  proto.m1.send_recv(proc_next, proc_next, tab_loc, tmp);
	  fusion_plus_petits(tab_loc, tmp);
	}
      } 
    }

    proto.m.gather(0, tab_loc, tab);
    if(proto.pid == 0) {
      print_vector(tab);
    }
  }

  /* Garde les n (n=a.size()) plus grands elements de a+b et garde le tout dans a */
  void fusion_plus_grands(vector<int>& tab1, vector<int>& tab2) {
    int size = tab1.size();
    vector<int> tmp; tmp.resize(size);
    int ptr1 = size-1, ptr2 = size-1;
    for (int i=size-1; i>=0; i--) {
      if (tab1[ptr1]>=tab2[ptr2]) {
	tmp[i]=tab1[ptr1];
	ptr1--;
      }
      else {
	tmp[i]=tab2[ptr2];
	ptr2--;
      }
    }
    tab1 = tmp;
  }

  /* Garde les n plus petits elements de a+b et garde le tout dans a */
  void fusion_plus_petits(vector<int>& tab1, vector<int>& tab2) {
    int size = tab1.size();
    vector<int> tmp; tmp.resize(size);
    int ptr1 = 0, ptr2 = 0;
    for (int i=0; i<size; i++) {
      if (tab1[ptr1]<=tab2[ptr2]) {
	tmp[i]=tab1[ptr1];
	ptr1++;
      }
      else {
	tmp[i]=tab2[ptr2];
	ptr2++;
      }
    }
    tab1 = tmp;
  }
 
  void print_vector(vector<int> vec) {
    for(auto i : vec) { cout << i << ", "; } cout << endl;
  }
};

int main(int argc, char** argv) {
  Mpiez<Prot,Proc> mp(argc, argv);
  mp.finalize();
  return 0;
}
