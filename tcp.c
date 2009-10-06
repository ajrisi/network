#include "tcp.h"

sock *sock_tcp_new(int timeout)
{
  return sock_new(AF_INET, SOCK_STREAM);
}







