#include <stdio.h>

#include <sock.h>
#include <tcp.h>
#include <udp.h>
#include <dns.h>

#define DATALEN 1024

int main(int argc, char **argv) {
  int i = 0;
  int child_pid = 0;
  char data[DATALEN] = {0};
  
  sock *s = sock_new_tcp(-1);
  if(s == NULL) {
    fprintf(stderr, "Failure to create a new socket\n");
    return -1;
  }

  if(sock_bind(s, resolve_host(NULL, 8081)) < 0) {
    fprintf(stderr, "Error! Could not bind\n");
    exit(-1);
  }

  sock_listen(s, 5);

  /* lets try a preforking server */
  for(i=0; i < 5; i++) {

    if((child_pid = fork()) == 0) {
      while(1) {
	sock *as = sock_accept(s);
	if(as != NULL) {
	  int rc;
	  while(sock_readtok(as, data, DATALEN, "\r\n", EXACT_DELIM | DROP_DELIM) > 0) {
	    printf("Got[%d]: %s\n", strlen(data), data);
	    memset(data, 0, DATALEN);
	  }
	  
	  /* write the HTML document */
	  sock_writestr(as, "HTTP/1.0 200 OK\r\n");
	  sock_writestr(as, "Content-Type: text/html\r\n\r\n");

	  if(sock_sendfile(as, "index.html") < 0) {
	    sock_writestr(as, "Could not open file!\n");
	  }

	  /* prep for next socket */
	  memset(data, 0, sizeof(data));
	  sock_free(as);
	  as = NULL;
	}
      }

    } else {
      printf("Spawned a child: %d\n", child_pid);
    }
    
  }

  wait(NULL);

  sock_free(s);
  return 0;
}
