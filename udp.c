#include "udp.h"

sock *sock_new_udp()
{
  return sock_new(PF_INET, SOCK_DGRAM);
}

int sock_recv(sock *s, void *buf, unsigned int len)
{
  if((s == NULL) ||
     (buf == NULL)) {
    return -1;
  }
  return recv(s->fd, buf, len, 0);
}

int sock_recvfrom(sock *s, void *buf, unsigned int len, struct sockaddr *from, socklen_t *fromlen)
{
  if((s == NULL) ||
     (buf == NULL) ||
     (from == NULL) ||
     (fromlen == NULL)) {
    return -1;
  }
  return recvfrom(s->fd, buf, len, 0, from, fromlen);
}

int sock_recv_all(sock *s, void *buf, unsigned int len)
{
  if((s == NULL) ||
     (buf == NULL)) {
    return -1;
  }
  return recv(s->fd, buf, len, MSG_WAITALL);
}

int sock_recvfrom_all(sock *s, void *buf, unsigned int len, struct sockaddr *from, socklen_t *fromlen)
{
  if((s == NULL) ||
     (buf == NULL) ||
     (from == NULL) ||
     (fromlen == NULL)) {
    return -1;
  }
  return recvfrom(s->fd, buf, len, MSG_WAITALL, from, fromlen);
}


