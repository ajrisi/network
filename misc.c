#include <stdlib.h>
#include <stdio.h>

#include "misc.h"

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

struct in_addr *resolve_host(const char *name)
{
  int i;
  struct in_addr *addr;
  struct hostent *hosts;

  addr = calloc(1, sizeof(struct in_addr));
  if(addr == NULL) {
    return NULL;
  }

  /* this is not natively IPv6 compatable */
  i = inet_pton(AF_INET6, name, &addr);
  if(!i) {
    /* assume that it was not an ip format address, so it was a name? */
    if((hosts = gethostbyname(name))) {
      for(i=0; hosts->h_addr_list[i]; i++) {
	memcpy(addr, hosts->h_addr_list[i], sizeof(addr));
      }

    } else {
      return NULL;
    }
  }

  return addr;
}

