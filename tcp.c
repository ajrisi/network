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

int sock_readline(sock *s, char *target, unsigned int maxlen)
{
  int strlen;
  int nread;
  char *tmp;
  char *lastchar;

  if((s == NULL) ||
     (target == NULL)) {
    return -1;
  }

  strlen = 0;

  tmp = malloc((maxlen+1) * sizeof(char));
  if(tmp == NULL) {
    return -1;
  }
  memset(tmp, '\0', maxlen+1);

  nread = recv(s->fd, tmp, maxlen, MSG_PEEK);
  if(nread < 0) {
    free(tmp);
    return nread;
  }

  /* we know at this point that tmp contains some data, up to maxlen,
     that has NOT been removed from the queue, we need to then look
     for a line delimeter to get len of next line, then, do a read for
     just that many characters into target, and return that code */
  lastchar = strpbrk(tmp, "\r\n");
  if(lastchar == NULL) {
    free(tmp);
    return -1;
  }

  /* last char is now the first instance of either a \r or \n, we can
     now move it forward while there are more of them */
  while((*lastchar != '\0') &&
	((*lastchar == '\r') ||
	 (*lastchar == '\n'))) {
    lastchar++;
  }

  /* we can now determine the length of the line by looking at the
     dist from start to end */
  strlen = lastchar - tmp;

  /* and return the result of a recv call for that many bytes */
  /* this might need to be replaced with the readall read fn */
  return recv(s->fd, target, strlen, 0);
}




