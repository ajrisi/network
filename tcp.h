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

sock *sock_new_tcp(int timeout);

int sock_listen(sock *s, int backlog);

sock *sock_accept(sock *s);

#endif /* _TCP_H_ */
