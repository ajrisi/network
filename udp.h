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

sock *sock_new_udp();

int sock_recv(sock *s, void *buf, unsigned int len);

int sock_recvfrom(sock *s, void *buf, unsigned int len, struct sockaddr *from, socklen_t *fromlen);

int sock_recv_all(sock *s, void *buf, unsigned int len);

int sock_recvfrom_all(sock *s, void *buf, unsigned int len, struct sockaddr *from, socklen_t *fromlen);

#endif /* _UDP_H_ */
