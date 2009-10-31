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

  /* save the type */
  s->type = type;

  s->listen = 0;

  /* if the domain was PF_INET, set the family */
  switch(domain) {
  case PF_INET:
    s->family = AF_INET;
    break;
  case PF_INET6:
    s->family = AF_INET6;
    break;
  default:
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
  /*l.l_onoff = 1;
  l.l_linger = 0;
  i = setsockopt(s->fd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));
  if(i < 0) {
    close(s->fd);
    free(s);
    return NULL;
    }*/

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

int sock_bind(sock *s, struct sockaddr *localaddr)
{
  int i;

  i = bind(s->fd, localaddr, SOCKADDR_SIZEOF(localaddr));
  if(i < 0) {
    return -1;
  }

  /* free the old local address if it existed */
  free(s->localaddr);

  /* save the local address */
  s->localaddr = localaddr;

  return 0;
}

int sock_connect(sock *s,
		 struct sockaddr *dstaddr,
		 struct sockaddr *localaddr)
{
  int i;

  if((s == NULL) ||
     (dstaddr == NULL)) {
    return -1;
  }

  /* call bind to bind to the local port first */
  if(localaddr) {
    i = sock_bind(s, localaddr);
    if(i != 0) {
      return -2;
    }
    free(s->localaddr);
    s->localaddr = localaddr;
  }

  /* do the call to connect - allow neg return for non blocking */
  i = connect(s->fd, dstaddr, SOCKADDR_SIZEOF(dstaddr));
  if((i < 0) && (errno != EINPROGRESS)) {
    return -3;
  }
  
  /* free the old remote, save the new one */
  free(s->remoteaddr);
  s->remoteaddr = dstaddr;
  
  return 0;
}

int sock_read(sock *s, char *buf, unsigned int size)
{
  if((s == NULL) ||
     (buf == NULL)) {
    return -1;
  }

  return read(s->fd, buf, size);
}

int sock_write(sock *s, void *buf, unsigned int size)
{
 if((s == NULL) ||
     (buf == NULL)) {
    return -1;
  }
 
 return write(s->fd, buf, size);
}

int sock_writestr(sock *s, char *str)
{
  printf("Send %s\n", str);
  return sock_write(s, str, strlen(str));
}

int sock_sendfile(sock *s, char *path)
{
  int fd;
  int nwritten;
  int nread;
  char buffer[SOCK_SENDFILE_BUFFSZ];
  /* open the file, do block writes to the socket until we reach the
     end of the file, or the socket throws an error */

  if(s == NULL) {
    return -1;
  }

  nwritten = 0;
  nread = 0;

  fd = open(path, O_RDONLY);
  if(fd == -1) {
    return -1;
  }

  /* TODO: this is not safe, it should handle partial reads and
     writes, and it doesnt (yet) */
  while((nread = read(fd, buffer, SOCK_SENDFILE_BUFFSZ)) > 0) {
    printf("sending: %s\n", buffer);
    nwritten += send(s->fd, buffer, nread, 0);
  } 
  
  close(fd);
  return nwritten;
}

int sock_set_nonblock(sock *s) 
{
  return set_nonblock(s->fd);
}

void sock_free(sock *s)
{
  if(s == NULL) return;

  /* close the sock if it is open */
  if(s->fd >= 0) {
    close(s->fd);
  }

  /* free the sockaddr memory */
  free(s->remoteaddr);
  free(s->localaddr);

  free(s);
}
