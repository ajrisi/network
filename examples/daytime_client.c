#include <stdio.h>

#include <sock.h>
#include <tcp.h>
#include <udp.h>
#include <dns.h>

int main(int argc, char **argv) {
  int i = 0;
  int child_pid = 0;
  char time[256] = {0};

  sock *s = sock_new_tcp(-1);
  if(s == NULL) {
    fprintf(stderr, "Failure to create a new socket\n");
    return -1;
  }

  if((i = sock_connect(s, resolve_host("chronos.rh.rit.edu", 13), NULL)) < 0) {
    fprintf(stderr, "Could not do connect call: %d\n", i);
    return -1;
  }

  if((i = sock_read(s, time, 256)) < 0) {
    fprintf(stderr, "Could not read from socket: %d\n", i);
    return -1;
  }

  printf("Time: %s\n", time);

  sock_free(s);
  return 0;
}
