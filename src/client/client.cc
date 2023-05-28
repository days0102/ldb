/*
 * @Author       : Outsider
 * @Date         : 2023-02-24 11:06:31
 * @LastEditors  : Outsider
 * @LastEditTime : 2023-05-28 12:23:32
 * @Description  : In User Settings Edit
 * @FilePath     : /ldb/src/client/client.cc
 */
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "arpa/inet.h"
#include "getopt.h"
#include "inc/defs.hh"
#include "inc/net/socket.hh"
#include "strings.h"
#include "sys/socket.h"
#include "unistd.h"
/**
 * @description: Use tcp socket to connect to host:port
 * @param  *host To be connected server host
 * @param  port  To be connected server port
 * @return Returns socket fd on success, -1 on failure
 */
auto tcpsocked(const char *host, int port) -> int {
  int socked_fd;

  // AF_INET(ipv4),SOCK_STREAM(TCP)
  if ((socked_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Create TCP Socket Error!" << std::endl;
    return socked_fd;
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(host);
  server_addr.sin_port = htons(port);
  bzero(&(server_addr.sin_zero), 8);

  if (connect(socked_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) ==
      -1) {
    std::cerr << "Failed to connect Server!" << std::endl;
    return -1;
  }

  return socked_fd;
}

auto main(int argc, char *argv[]) -> int {
  const char *server_host = "127.0.0.1";
  int default_port = 9999;
  int opt;
  extern char *optarg;
  while ((opt = getopt(argc, argv, "p:")) > 0) {
    switch (opt) {
      case 'p':
        default_port = atoi(optarg);
        break;

      default:
        break;
    }
  }

  int socket_fd;
  if ((socket_fd = tcpsocked(server_host, default_port)) < 0) {
    return 0;
  }

  std::string command;
  std::array<char, BUF_SIZE_MAX> recv_buf;
  int recv_len;

  while (true) {
    std::cout << "ldb > ";
    std::getline(std::cin, command);
    if (command == "exit") {
      break;
    }

    if (write(socket_fd, command.c_str(), command.size()) < 0) {
      std::cerr << "Write Fail" << std::endl;
    }
    memset(recv_buf.data(), 0, BUF_SIZE_MAX);

    while ((recv_len = recv(socket_fd, recv_buf.data(), BUF_SIZE_MAX, 0)) > 0) {
      std::string recv_msg(recv_buf.data());
      std::cout << recv_msg << std::endl;
      if (recv_len != BUF_SIZE_MAX) {
        break;
      }
    }

    if (recv_len < 0) {
      std::cerr << "Connection was broken!" << std::endl;
      break;
    }
    if (recv_len == 0) {
      std::cout << "Connection has been closed" << std::endl;
      break;
    }
  }

  close(socket_fd);
  return 0;
}