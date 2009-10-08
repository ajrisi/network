#include "tcp.h"

sock *sock_new_tcp(int timeout)
{
  return sock_new(AF_INET, SOCK_STREAM);
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
  struct sockaddr remote;
  socklen_t remote_len;

  struct sockaddr_in *rin;

  if(s == NULL) {
    return NULL;
  }

  if(s->listen != 1) {
    return NULL;
  }

  as = calloc(1, sizeof(sock));
  if(as == NULL) {
    return NULL;
  }
  
  /* actually accept here */
  remote_len = sizeof(remote);
  i = accept(s->fd, &remote, &remote_len);

  if(i < 0) {
    free(as);
    return NULL;
  }

  as->fd = i;

  as->remoteaddr.addr = (struct in_addr*)calloc(1, sizeof(struct in_addr));
  if(as->remoteaddr.addr == NULL) {
    free(as);
    return NULL;
  }

  /* copy over the remote address */
  rin = (struct sockaddr_in*)&remote;
  memcpy(as->remoteaddr.addr, &(rin->sin_addr),
	 sizeof(rin->sin_addr));

  as->family = rin->sin_family;
  as->remoteport = rin->sin_port;

  return as;
}






