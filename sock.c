#include "sock.h"

sock *sock_new(int domain, int type)
{
  sock *s;
  int sockopt;
  struct linger l;
  int i;

  s = (sock*)calloc(1, sizeof(sock));
  if(s == NULL) {
    return NULL;
  }

  /* save the domain */
  s->domain = domain;

  /* if the domain was PF_INET, set the family */
  if(domain == PF_INET) {
    s->family = AF_INET;
  } else {
    s->family = AF_UNSPEC;
  }

  /* no timeout */
  s->timeout = -1;

  /* do the socket call */
  s->fd = socket(domain, type, 0);
  if(s->fd < 0) {
    /* the socket call did not work, so return NULL */
    free(s);
    return NULL;
  }

  /* fix the linger opations so that we are not left in a TIME WAIT on
     close */
  l.l_onoff = 1;
  l.l_linger = 0;
  i = setsockopt(s->fd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));
  if(i < 0) {
    close(s->fd);
    free(s);
    return NULL;
  }

  /* set reuse so that re-opening one that wasnt closed doesnt take
     forever */
  sockopt = 1;
  i = setsockopt(s->fd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt));
  if(i < 0) {
    close(s->fd);
    free(s);
    return NULL;
  }

  return s;
}

int sock_bind(sock *s, const struct in_addr *localaddr, unsigned int localport)
{
  struct sockaddr_in local;
  int i;

  memset(&local, 0, sizeof(local));
  local.sin_family = s->family;
  local.sin_port = localport;

  /* the localaddr is optional, we might only want to connect to the
     local port */
  if(localaddr) {
    memcpy(&local.sin_addr, localaddr, sizeof(local.sin_addr));
  }

  i = bind(s->fd, (struct sockaddr*)&local, sizeof(local));
  if(i < 0) {
    return -2;
  }

  return 0;
}

int sock_connect(sock *s,
		   const struct in_addr *dstaddr, unsigned int dstport,
		   const struct in_addr *localaddr, unsigned int localport)
{
  int i;
  struct sockaddr_in dst;

  if(s == NULL) {
    return -1;
  }

  /* call bind to bind to the local port first */
  if(localaddr || localport) {
    i = sock_bind(s, localaddr, localport);
    if(i != 0) {
      return -2;
    }
  }

  /* now, create the remote address structure */
  memset(&dst, 0, sizeof(dst));
  dst.sin_family = s->family;
  dst.sin_port = dstport;
  memcpy(&dst.sin_addr, dstaddr, sizeof(dst.sin_addr));

  /* set this socket to non-blocking. Might not want to do this in
     every scenario */
  if((i = fcntl(s->fd, F_GETFL, 0)) >= 0) {
    i = fcntl(s->fd, F_SETFL, i | O_NONBLOCK);
  }
  if(i < 0) {
    return -3;
  }

  /* do the call to connect - because its non blocking, it can return
     neg. with errno saying its starting to work */
  i = connect(s->fd, (struct sockaddr *)&dst, sizeof(dst));
  if((i < 0) && (errno != EINPROGRESS)) {
    return -4;
  }
  

  return 0;
}

void sock_free(sock *s)
{
  /* close the sock if it is open */
  if(s->fd >= 0) {
    close(s->fd);
  }
  free(s);
}
