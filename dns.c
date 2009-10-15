#include "dns.h"

struct sockaddr *resolve_host(const char *name, unsigned int port)
{
  int i;
  struct sockaddr *addr;
  struct addrinfo *res;

  addr = NULL;
  res = NULL;

  /* if the name is null, we assume the special case where they want
     an IPv4 with only the port and the family set */
  if(name == NULL) {
    addr = calloc(1, sizeof(struct sockaddr_in));
    if(addr == NULL) {
      return NULL;
    }
    addr->sa_family = AF_INET;
    port_set(addr, port);

  } else {
    i = getaddrinfo(name, NULL, NULL, &res);
    if((i != 0) ||
       (res == NULL)) {
      return NULL;
    }
    
    addr = calloc(1, res->ai_addrlen);
    if(addr == NULL) {
      freeaddrinfo(res);
      return NULL;
    }

    memcpy(addr, res->ai_addr, res->ai_addrlen);
    
    /* set the port by number */
    port_set(addr, port);
    
    freeaddrinfo(res);
  }

  return addr;
}

char *get_hostname(struct sockaddr *addr, char *buf, unsigned int buflen)
{
  int rc;

  rc = getnameinfo(addr, SOCKADDR_SIZEOF(addr), buf, buflen, NULL, 0, NI_NAMEREQD);
  if(rc != 0) {
    return NULL;
  } else {
    return buf;
  }

}

