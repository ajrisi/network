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

typedef struct sock_s sock;
struct sock_s {
  int fd;
  int domain;
  int timeout;
};

#endif /* _SOCK_H_ */
