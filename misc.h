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

#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


/**
 * Create a nice bool type
 * 
 */
#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

#ifndef __cplusplus
# ifndef bool
#  define bool unsigned char
# endif
#endif

#define BOOL_TO_STR(__var__) (__var__ ? "TRUE" : "FALSE")

/** 
 * Sets the file descriptor fd to non blocking
 * 
 * @param fd the file descriptor
 * 
 * @return 0 on success, negative values on failure
 */
int set_nonblock(int fd);

/** 
 * Resolves a name into an in_addr structure
 * 
 * @param dst the location of the in_addr structure to fill
 * @param name the name of the host, in IP form, or a domain name
 * 
 * @return 0 on success, negative values on failure 
 */
int resolve_host(struct in_addr *dst, const char *name);

#endif /* _MISC_H_ */
