#pragma once

namespace mmpi {
  template <int N, typename A>
  struct Message {
    Message() {}

    void send(int id_proc, A data) {
      cout << "Send " << data << " to " << id_proc << endl;
    }

    void recv(int id_proc, A & buffer) {
      cout << "Recv " << buffer << " from " << id_proc << endl;
    }
  };
};
