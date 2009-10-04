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
#include <stdlib.h>
#include <unistd.h>

typedef struct sock_s sock;
struct sock_s {
  int fd;
  int domain;
  int timeout;
};

sock *socket_new(int domain, int type);

void socket_free(sock *s);

#endif /* _SOCK_H_ */
