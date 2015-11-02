#include <iostream>
#include <vector>

#include <mpiez/include/mpiez.hpp>

using namespace std;
using namespace mpiez;

struct Prot : Protocol {
  Prot(int pid, int nprocs) : Protocol(pid, nprocs) {}
  ColMessage<int> m;
};

struct Proc : Process<Prot> {
  Proc(Prot & p) : Process(p) {}

  void routine() {
    global::syncExec(this, &Proc::test, 2);
  }

  void test(int a) {
    cout << a << endl;
  }
};

int main(int argc, char ** argv) {
  Mpiez<Prot, Proc> ad(argc, argv);
  ad.finalize();
  return 0;
}
