#include <iostream>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<int> mc;
  Message<0,int> m;
};

struct Proc : Process<Prot> {
  int* tab;
  int n;
  int pivot;
  
  Proc(Prot & p, int argc, char** argv) : Process(p, argc, argv) {
    n = atoi(argv[1]);
    tab = new int[n];

    srand(time(NULL)+proto.pid);
    for(int i = 0; i < n; i++) {
      tab[i] = rand()%10;
    }
  }
  
  void routine() {
    global::syncExec(this, &Proc::print_tab, tab);

    get_pivot();

    /* On va chercher le nombre d'éléments <= pivot et > pivot */
    int inf;
    int sup;
    get_inf_sup(inf,sup);

    /* On récupère le nombre d'éléments plus petits présents avant le proc courant */
    int inf_less_me;
    int sum_inf; //somme éléments plus <= pivot avant proc + elements plus petit proc
    get_inf_less_me(inf, inf_less_me);
    sum_inf = inf_less_me+inf;
    //get_sup

    /* On détermine à qui on va envoyer les plus petits éléments */
    int proc_recv;
    if(proto.pid == 0) {
      proc_recv = 0;
    } else {
      if(inf_less_me%n == 0 && inf_less_me != n) {
	proc_recv = (inf_less_me/n)-1;
      } else {
	proc_recv = inf_less_me/n;
      }
    }

    cout << "Je suis " << proto.pid << " et j'envoie à " << proc_recv << endl;
  }

  void get_pivot() {
    if(proto.pid == 0) {
      pivot = tab[0];
      cout << "[PIVOT = " << pivot << "]" << endl;
    }
    proto.mc.bcast(0, pivot);
  }

  /* Va chercher le nombre d'éléments inférieurs ou égal au pivot, et supérieur au pivot */
  void get_inf_sup(int& inf, int& sup) {
    inf = 0;
    sup = 0;
    for(int i = 0; i < n; i++) {
      if(tab[i] <= pivot) {
	inf++;
      } else {
	sup++;
      }
    }
  }


  /* Va chercher le nombre d'éléments plus petits avant le proc courant */
  void get_inf_less_me(int inf, int& res) {
    if(proto.pid == 0) {
      res = 0;
      proto.m.send(1, inf);
    } else if(proto.pid > 0 && proto.pid < proto.nprocs-1) {
      proto.m.recv(proto.pid-1, res);
      int s = res+inf;
      proto.m.send(proto.pid+1, s);
    } else {
      proto.m.recv(proto.pid-1, res);
    }
  }
  
  void print_tab(int* tab) {
    cout << "Proc " << proto.pid << " : " << endl;
    for(int i = 0; i < n; i++) {
      cout << tab[i] << ", ";
    }
    cout << endl;
    if(proto.pid == proto.nprocs-1) {
      cout << "################################################" << endl;
    }
  }

  void print_tab_inf_sup(int* tab) {
    cout << "Proc " << proto.pid << " : ";
    for(int i = 0; i < proto.nprocs; i++) {
      cout << tab[i] << ", ";
    }
    cout << endl;
    if(proto.pid == proto.nprocs-1) {
      cout << "################################################" << endl;
    }
  }

};

int main(int argc, char** argv) {
  Mpiez<Prot, Proc> mpi(argc, argv);
  mpi.finalize();
  return 0;
}
