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

  if(sock_bind(s, resolve_host(NULL, 5956)) < 0) {
    fprintf(stderr, "Error! Could not bind\n");
    exit(-1);
  }

  sock_listen(s, 1);

  sock *as = sock_accept(s);
  if(as != NULL) {
    while(sock_readtok(as, data, DATALEN, "\r\n", EXACT_DELIM | DROP_DELIM) >= 0) {
      printf("Got: %s\n", data);
      memset(data, 0, DATALEN);
    }


    sock_free(as);
  }
  
  sock_free(s);
  return 0;
}
