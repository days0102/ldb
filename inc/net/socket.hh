/*
 * @Author       : Outsider
 * @Date         : 2023-05-27 21:51:05
 * @LastEditors  : Outsider
 * @LastEditTime : 2023-05-27 22:23:22
 * @Description  : In User Settings Edit
 * @FilePath     : /ldb/inc/net/socket.hh
 */
#pragma once

#include "netdb.h"
#include "netinet/tcp.h"
#include "sys/socket.h"
#include "unistd.h"

const unsigned short SOCKET_DEFAULT_TIMEOUT = 10000;

class Socket {
 private:
  int fd_;
  struct sockaddr_in address_;
  struct sockaddr_in peer_address_;
  int timeout_;

 public:
  Socket();
  Socket(unsigned short port, int timeout = SOCKET_DEFAULT_TIMEOUT);

  ~Socket();

  void SetTimeout(int seconds = SOCKET_DEFAULT_TIMEOUT);
  int DisableNagle();
};
