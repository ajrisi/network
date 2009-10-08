#include "tcp.h"

sock *sock_new_tcp(int timeout)
{
  return sock_new(AF_INET, SOCK_STREAM);
}

int sock_listen(sock *s, int backlog)
{
  if(s->type != SOCK_STREAM) {
    return -1;
  }
  return listen(s->fd, backlog);
}








