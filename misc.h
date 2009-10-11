/**
 * @file   misc.h
 * @author Adam Risi <ajrisi@gmail.com>
 * @date   Sat Oct  3 19:21:04 2009
 * 
 * @brief  Misc. routines and defines
 * 
 * 
 */

#ifndef _MISC_H_
#define _MISC_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define SOCKADDR_SIZEOF(x) (x->sa_family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6))

void port_set(struct sockaddr *sa, unsigned int port);

unsigned int port_get(struct sockaddr *sa);

int set_nonblock(int fd);

#endif /* _MISC_H_ */
