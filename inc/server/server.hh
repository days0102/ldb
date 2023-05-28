/*
 * @Author       : Outsider
 * @Date         : 2023-03-24 11:50:08
 * @LastEditors  : Outsider
 * @LastEditTime : 2023-05-27 22:11:37
 * @Description  : In User Settings Edit
 * @FilePath     : /ldb/inc/server/server.hh
 */
#pragma once

#include "inc/net/socket.hh"

class ServerParam {
 public:
};

class Server {
 public:
  Server();

 private:
  // Socket socket;
  // 接受 Client 连接地址
  long listen_addr_;
  unsigned short port_;  // 服务端口
};