#include "tcp.h"

sock *sock_new_tcp(int timeout)
{
  return sock_new(PF_INET, SOCK_STREAM);
}

int sock_listen(sock *s, int backlog)
{
  int i = -1;
  
  if(s->type != SOCK_STREAM) {
    return -1;
  }

  i = listen(s->fd, backlog);
  if(i == 0) {
    s->listen = 1;
  }

  return i;
}

sock *sock_accept(sock *s)
{
  int i;
  sock *as;
  struct sockaddr *remote;
  socklen_t rlen;

  if(s == NULL) {
    return NULL;
  }

  if((s->listen != 1) ||
     (s->localaddr == NULL)) {
    return NULL;
  }

  as = sock_new(s->domain, s->type);
  if(as == NULL) {
    return NULL;
  }

  remote = calloc(1, SOCKADDR_SIZEOF(s->localaddr));
  if(remote == NULL) {
    sock_free(as);
    return NULL;
  }
  
  /* actually accept here */
  rlen = SOCKADDR_SIZEOF(remote);
  i = accept(s->fd, remote, &rlen);

  if(i < 0) {
    free(remote);
    sock_free(as);
    return NULL;
  }

  as->fd = i;
  as->remoteaddr = remote;
  as->remoteport = port_get(remote);

  return as;
}






