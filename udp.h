/**
 * @file   udp.h
 * @author Adam Risi <ajrisi@gmail.com>
 * @date   Sat Oct  3 18:39:29 2009
 * 
 * @brief  This file contains the routines related to UDP networking
 * 
 * 
 */


#ifndef _UDP_H_
#define _UDP_H_

#include "sock.h"

typedef struct udp_sock_s udp_sock;
struct udp_sock_s {
  sock *s;
};

udp_sock *udp_sock_new(int timeout);

void udp_sock_free(udp_sock *u);

#endif /* _UDP_H_ */
