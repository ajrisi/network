#include "udp.h"

sock *sock_new_udp()
{
  return sock_new(PF_INET, SOCK_DGRAM);
}

int sock_recv(sock *s, void *buf, unsigned int len)
{
  return recv(s->fd, buf, len, 0);
}

int sock_recv_all(sock *s, void *buf, unsigned int len)
{
  return recv(s->fd, buf, len, MSG_WAITALL);
}

