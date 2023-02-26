/*
 * @Author       : Outsider
 * @Date         : 2023-02-24 11:15:56
 * @LastEditors  : Outsider
 * @LastEditTime : 2023-02-26 20:19:31
 * @Description  : In User Settings Edit
 * @FilePath     : /ldb/src/server/server.cc
 */

#include <array>
#include <cstring>
#include <iostream>

#include "inc/defs.hh"
#include "netdb.h"
#include "netinet/tcp.h"
#include "sys/socket.h"
#include "unistd.h"

auto main() -> int {
  std::cout << "server" << std::endl;

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    std::cerr << "Server Create TCP Socket Error!" << std::endl;
    return -1;
  }

  int default_port = 9999;
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(default_port);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    std::cerr << "Failed to bind in Server" << std::endl;
    return -1;
  }

  if (listen(server_fd, 5) < 0) {
    std::cerr << "Failed to listen in Server" << std::endl;
    return -1;
  }

  while (true) {
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    while (client_fd != -1) {
      int yes = 1;
      size_t ret = setsockopt(client_fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes));
      std::array<char, BUF_SIZE_MAX> recv_buf;

      ret = recv(client_fd, recv_buf.data(), BUF_SIZE_MAX, 0);
      if (ret > 0) {
        std::cerr << "Recv data from client, data: " << std::string(recv_buf.data())
                  << std::endl;

        ret = write(client_fd, recv_buf.data(), strlen(recv_buf.data()));
        if (ret != strlen(recv_buf.data())) {
          std::cerr << "Send data error." << std::endl;
        }
        memset(recv_buf.data(), 0, strlen(recv_buf.data()));
      } else {
        std::cerr << "Fail to recv data" << std::endl;
      }
    }
  }

  // close socket
  close(server_fd);
  return 0;
}