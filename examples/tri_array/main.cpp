#include <iostream>
#include <vector>
#include <algorithm>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<int> m;
  Message<0, int> m1;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}
  
  void routine() {
    srand(proto.pid);
    vector<int> tab;
    vector<int> tab_loc;
    
    int tot_size = atoi(argv[1]);

    if(proto.pid == 0) {
      for(int i = 0; i < tot_size; i++) {
	tab.push_back(rand()%100);
      }
      print_vector(tab);
    }

    
    int proc_next = proto.pid+1;
    int proc_prev = proto.pid-1;
      
    int nprocs_left = tot_size%proto.nprocs;
    int size_loc    = tot_size/proto.nprocs;
    int size_left   = size_loc;
    int size_right  = size_loc;
    if(proc_prev < nprocs_left)
      size_left += 1;
    if(proc_next < nprocs_left)
      size_right += 1;
    
    if(proto.pid < nprocs_left)
      size_loc++;
    
    tab_loc.resize(size_loc);
    proto.m.scatterv(0, tab.data(), tab_loc.data(), tot_size);

    sort(tab_loc.begin(), tab_loc.end());

    for(int i = 0; i < proto.nprocs; i++) {
      vector<int> tmp;
      if(i%2 == 0) {
	if(proto.pid%2 == 0 && proc_next < proto.nprocs) {
	  tmp.resize(size_right);
	  proto.m1.send_recv(proc_next, proc_next, tab_loc.data(), tmp.data(), size_loc, size_right);
	  fusion_plus_petits(tab_loc, tmp);
	} else if(proto.pid%2 != 0) {
	  tmp.resize(size_left);
	  proto.m1.send_recv(proc_prev, proc_prev, tab_loc.data(), tmp.data(), size_loc, size_left);
	  fusion_plus_grands(tab_loc, tmp);
	}
      } else {
	if(proto.pid%2 == 0 && proto.pid != 0) {
	  tmp.resize(size_left);
	  proto.m1.send_recv(proc_prev, proc_prev, tab_loc.data(), tmp.data(), size_loc, size_left);
	  fusion_plus_grands(tab_loc, tmp);
	} else if(proto.pid%2 != 0 && proc_next < proto.nprocs) {
	  tmp.resize(size_right);
	  proto.m1.send_recv(proc_next, proc_next, tab_loc.data(), tmp.data(), size_loc, size_right);
	  fusion_plus_petits(tab_loc, tmp);
	}
      } 
    }
    
    proto.m.gatherv(0, tab_loc.data(), tab.data(), tot_size);
    if(proto.pid == 0) {
      print_vector(tab);
    }
  } 

  /* Garde les n (n=a.size()) plus grands elements de a+b et garde le tout dans a */
  void fusion_plus_grands(vector<int>& tab1, vector<int>& tab2) {
    int size = tab1.size();
    vector<int> tmp; tmp.resize(size);
    int ptr1 = tab1.size()-1, ptr2 = tab2.size()-1;
    for (int i=tab1.size()-1; i>=0; i--) {
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
    int n1 = tab1.size();
    int n2 = tab2.size();
    int size = (n1 > n2) ? n2 : n1;
    vector<int> tmp; tmp.resize(n1);
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
    
    if (n1>n2) {
      if (ptr2>=n2)
	tmp[n1-1] = tab1[ptr1];
      else 
	tmp[n1-1] = (tab1[ptr1]<=tab2[ptr2]) ? tab1[ptr1] : tab2[ptr2];
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
