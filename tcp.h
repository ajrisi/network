/**
 * @file   tcp.c
 * @author Adam Risi <ajrisi@gmail.com>
 * @date   Sat Oct  3 18:25:59 2009
 * 
 * @brief  This file contains the routines used for TCP operations
 * 
 * 
 */

#ifndef TCP_H
#define TCP_H

#include <string.h>
#include "sock.h"

sock *sock_new_tcp(int timeout);

int sock_listen(sock *s, int backlog);

sock *sock_accept(sock *s);

enum sock_readtok_flags {
  DROP_DELIM  = 1,
  LEAVE_DELIM = 2,
  TAKE_DELIM  = 4,
  EXACT_DELIM = 8,
  ANY_DELIM   = 16,
};
int sock_readtok(sock *s, char *target, unsigned int maxlen, char *delim, enum sock_readtok_flags flags);


#endif /* TCP_H */
