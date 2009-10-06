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

int resolve_host(struct in_addr *dst, const char *name)
{
  int i;
  struct in_addr addr;
  struct hostent *hosts;
  char n[1024] = {0};

  memset(&addr, 0, sizeof(struct in_addr));

  /* this is not natively IPv6 compatable */
  i = inet_pton(AF_INET, name, &addr);
  if(!i) {
    /* assume that it was not an ip format address, so it was a name? */
    if((hosts = gethostbyname(name))) {
      for(i=0; hosts->h_addr_list[i]; i++) {
	printf("h_addr_list[%d] = %s\n", i, inet_ntop(AF_INET, hosts->h_addr_list[i], n, 1024));
	memcpy(&addr, hosts->h_addr_list[i], sizeof(addr));
      }

    } else {
      return -1;
    }
  }

  memcpy(dst, &addr, sizeof(dst));

  return 0;
}
