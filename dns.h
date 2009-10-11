#ifndef _DNS_H_
#define _DNS_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#include "misc.h"

struct sockaddr *resolve_host(const char *name, unsigned int port);

#endif
