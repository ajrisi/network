/**
 * @file   tcp.c
 * @author Adam Risi <ajrisi@gmail.com>
 * @date   Sat Oct  3 18:25:59 2009
 * 
 * @brief  This file contains the routines used for TCP operations
 * 
 * 
 */

#ifndef _TCP_H_
#define _TCP_H_

#include "sock.h"

typedef struct tcp_sock_s tcp_sock;
struct tcp_sock_s {
  sock *s;
};

tcp_sock *tcp_sock_new(int timeout);

void tcp_sock_free(tcp_sock *t);

#endif /* _TCP_H_ */
