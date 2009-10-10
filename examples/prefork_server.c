#include <stdio.h>

#include "sock.h"
#include "tcp.h"
#include "udp.h"

int main(int argc, char **argv) {
  int i = 0;
  int child_pid = 0;
  char time[256] = {0};

  sock *s = sock_new_tcp(-1);
  if(s == NULL) {
    fprintf(stderr, "Failure to create a new socket\n");
    return -1;
  }

  if(sock_bind(s, NULL, 5956) < 0) {
    fprintf(stderr, "Error! Could not bind\n");
    exit(-1);
  }

  sock_listen(s, 5);

  /* lets try a forking, prethreading server */
  for(i=0; i < 5; i++) {

    if((child_pid = fork()) == 0) {
      while(1) {
	sock *as = sock_accept(s);
	if(as != NULL) {
	  sock_read(as, time, 256);
	  printf("%d Got: %s\n", getpid(), time);
	  memset(time, 0, sizeof(time));
	  sock_free(as);
	  as = NULL;
	}
      }

    } else {
      printf("Spawned a child: %d\n", child_pid);
    }
    
  }

  wait(NULL);


  /*


  if(sock_connect(s, resolve_host("chronos.rh.rit.edu"), 13, NULL, 0) < 0) {
    fprintf(stderr, "Could not do connect call\n");
    return -1;
  }

  if((i = sock_read(s, time, 256)) < 0) {
    fprintf(stderr, "Could not read from socket: %d\n", i);
    return -1;
  }

  printf("Time: %s\n", time);
  */


  sock_free(s);
  return 0;
}