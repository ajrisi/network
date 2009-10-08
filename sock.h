/**
 * @file   sock.h
 * @author Adam Risi <ajrisi@gmail.com>
 * @date   Sat Oct  3 19:05:20 2009
 * 
 * @brief  This file contains general socket routines
 * 
 * 
 */

#ifndef _SOCK_H_
#define _SOCK_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "misc.h"

typedef struct sock_s sock;
struct sock_s {
  int fd;
  int domain;
  int family;
  int timeout;
  int type;

  unsigned short localport;
  unsigned short remoteport;

  union {
    struct in_addr *addr;
    struct in6_addr *addr6;
  } localaddr, remoteaddr;
  
};

sock *sock_new(int domain, int type);

/** 
 * Binds a socket to a local address and port
 * 
 * @param s the socket
 * @param localaddr local address
 * @param localport local port
 * 
 * @return 0 on success, <0 on failure
 */
int sock_bind(sock *s, struct in_addr *localaddr, unsigned int localport);

int sock_connect(sock *s,
		   struct in_addr *dstaddr, unsigned int dstport,
		   struct in_addr *localaddr, unsigned int localport);

int sock_read(sock *s, char *buf, unsigned int size);

int sock_set_nonblock(sock *s);

void sock_free(sock *s);

#endif /* _SOCK_H_ */
