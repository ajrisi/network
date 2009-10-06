#include "tcp.h"

sock *sock_new_tcp(int timeout)
{
  return sock_new(AF_INET, SOCK_STREAM);
}







