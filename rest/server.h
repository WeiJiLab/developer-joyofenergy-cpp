#ifndef DEVELOPER_JOYOFENERGY_CPP_BEAST_SERVER_H
#define DEVELOPER_JOYOFENERGY_CPP_BEAST_SERVER_H

#include <memory>
#include <thread>
#include <vector>

namespace server_detail {
class impl;
}

class server {
 public:
  explicit server(int concurrency);

  ~server();

  void run(const char *address, unsigned short port);

 private:
  std::unique_ptr<server_detail::impl> impl;
  int concurrency;
  std::vector<std::thread> threads;
};

#endif  // DEVELOPER_JOYOFENERGY_CPP_BEAST_SERVER_H
