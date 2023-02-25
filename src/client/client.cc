/*
 * @Author       : Outsider
 * @Date         : 2023-02-24 11:06:31
 * @LastEditors  : Outsider
 * @LastEditTime : 2023-02-25 09:52:35
 * @Description  : In User Settings Edit
 * @FilePath     : /ldb/src/client/client.cc
 */
#include <getopt.h>
#include <netdb.h>
#include <stdlib.h>

#include <iostream>

/**
 * @description: tcp socket connect to host:port
 * @param  *host
 * @param  port
 * @return socket fd if success
 */
int tcpsock(const char *host, int port) { struct hostent server_host; }

auto main(int argc, char *argv[]) -> int {
  int defport = 9901;
  int opt;
  extern char *optarg;
  while ((opt = getopt(argc, argv, "p:")) > 0) {
    switch (opt) {
      case 'p':
        defport = atoi(optarg);
        break;

      default:
        break;
    }
  }
}