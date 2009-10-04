#include "sock.h"

sock *socket_new(int domain, int type)
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

void socket_free(sock *s)
{
  /* close the sock if it is open */
  if(s->fd >= 0) {
    close(s->fd);
  }
  free(s);
}
