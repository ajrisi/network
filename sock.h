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

#include "misc.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

typedef struct sock_s sock;
struct sock_s {
  int fd;
  int domain;
  int family;
  int timeout;
  int type;

  int listen;

  unsigned short localport;
  unsigned short remoteport;

  struct sockaddr *localaddr;
  struct sockaddr *remoteaddr;
  
};

sock *sock_new(int domain, int type);

/** 
 * Binds a socket to a local address and port
 * 
 * @param s the socket
 * @param localaddr local address
 * 
 * @return 0 on success, <0 on failure
 */
int sock_bind(sock *s, struct sockaddr *localaddr);

int sock_connect(sock *s,
		 struct sockaddr *dstaddr,
		 struct sockaddr *localaddr);

int sock_write(sock *s, void *buf, unsigned int size);

int sock_read(sock *s, char *buf, unsigned int size);

int sock_set_nonblock(sock *s);

void sock_free(sock *s);

#endif /* _SOCK_H_ */
