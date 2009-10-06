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


#endif /* _MISC_H_ */
