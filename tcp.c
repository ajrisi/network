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

int sock_readtok(sock *s, char *target, unsigned int maxlen, char *delim, enum sock_readtok_flags flags)
{
  int len;
  int nread;
  int nread_tmp;
  char *tmp;
  char *lastchar;
  char *startdelim;
  char *enddelim;
  int delimlen;

  if((s == NULL) ||
     (target == NULL)) {
    return -1;
  }

  len = 0;

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
  if(flags & EXACT_DELIM) {
    delimlen = strlen(delim);
    lastchar = strstr(tmp, delim);
    startdelim = lastchar;
    enddelim = lastchar + delimlen;
  } else {
    delimlen = 0;
    lastchar = strpbrk(tmp, delim);
    startdelim = lastchar;
    enddelim = startdelim;

    while((*enddelim != '\0') &&
	  (strchr(delim, *enddelim) != NULL)) {
      delimlen++;
      enddelim++;
    }

  }
  if(lastchar == NULL) {
    free(tmp);
    return -1;
  }

  /* now, enddelim is the end of the delim, and delimlen is correct */
  /* we can now determine the length of the line by looking at the
     dist from start to end */
  len = lastchar - tmp;

  /* if we are leaving the delim, read the len, if we are taking
     the delim, read len + delim len, and if we are dropping delim,
     then read len, then read delimlen into tmp */

  if(flags & LEAVE_DELIM) {
    nread = recv(s->fd, target, len, 0);
    nread_tmp = nread;
  } else if(flags & DROP_DELIM) {
    nread = recv(s->fd, tmp, len+delimlen, 0);
  } else {
    /* TAKE DELIM */
    nread = recv(s->fd, target, len+delimlen, 0);
  }

  if(nread < 0) {
    free(tmp);
    return nread;
  }

  if(flags & DROP_DELIM) {
    /* copy from tmp the len of chars into target */
    memcpy(target, tmp, len);
    nread -= delimlen;
  }

  free(tmp);

  return nread;
}




