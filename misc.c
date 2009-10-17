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

int sockaddr_cmp(struct sockaddr *sa1, struct sockaddr *sa2)
{
  struct sockaddr_in *sai1, *sai2;
  struct sockaddr_in6 *sai61, *sai62;

  if(sa1->sa_family != sa2->sa_family) {
    return 1;
  }

  switch(sa1->sa_family) {
  case AF_INET:
    sai1 = (struct sockaddr_in *)sa1;
    sai2 = (struct sockaddr_in *)sa2;
    if((sai1->sin_port != sai2->sin_port) ||
       (memcmp(sai1, sai2, sizeof(struct sockaddr_in)) != 0)) {
      return 1;
    }
    break;
  case AF_INET6:
    sai61 = (struct sockaddr_in6 *)sa1;
    sai62 = (struct sockaddr_in6 *)sa2;
    if((sai61->sin6_port != sai62->sin6_port) ||
       (memcmp(sai61, sai62, sizeof(struct sockaddr_in6)) != 0)) {
      return 1;
    }
    break;
  default:
    return 1;
  }
  
  return 0;
}

