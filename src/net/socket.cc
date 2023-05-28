/*
 * @Author       : Outsider
 * @Date         : 2023-05-27 22:04:54
 * @LastEditors  : Outsider
 * @LastEditTime : 2023-05-28 11:58:51
 * @Description  : In User Settings Edit
 * @FilePath     : /ldb/src/net/socket.cc
 */
#include "inc/net/socket.hh"
Socket::Socket() {}
Socket::Socket(unsigned short port, int timeout) {}

Socket::~Socket() {}

int Socket::DisableNagle() { return 0; }