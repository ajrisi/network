#include "misc.h"

void port_set(struct sockaddr *sa, unsigned int port)
{

  switch(sa->sa_family) {
  default:
  case AF_INET:
    ((struct sockaddr_in*)sa)->sin_port = htons(port);
    break;
  case AF_INET6:
    ((struct sockaddr_in6*)sa)->sin6_port = htons(port);
    break;
  }

}

unsigned int port_get(struct sockaddr *sa)
{
  switch(sa->sa_family) {
  default:
  case AF_INET:
    return ((struct sockaddr_in*)sa)->sin_port;
    break;
  case AF_INET6:
    return ((struct sockaddr_in6*)sa)->sin6_port;
    break;
  }
}

int set_nonblock(int fd)
{
  int flags;

  if((flags = fcntl(fd, F_GETFL, 0)) < 0) {
    return -1;
  }

  flags |= O_NONBLOCK;

  if(fcntl(fd, F_SETFL, flags) < 0) {
    return -2;
  }

  return 0;
}

struct sockaddr *sockaddr_dup(struct sockaddr *sa)
{
  struct sockaddr *new_sa;

  if(sa == NULL) {
    return NULL;
  }

  new_sa = (struct sockaddr *)calloc(1, SOCKADDR_SIZEOF(sa));
  if(new_sa == NULL) {
    return NULL;
  }

  memcpy(new_sa, sa, SOCKADDR_SIZEOF(sa));

  return new_sa;
}


