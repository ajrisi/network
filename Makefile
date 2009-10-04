all:	tcp.o udp.o sock.o

tcp.o:	tcp.h tcp.c
	gcc -Wall -ansi -o tcp.o -c tcp.c

udp.o:	udp.h udp.c
	gcc -Wall -ansi -o ucp.o -c udp.c

sock.o:	sock.h sock.c
	gcc -Wall -ansi -o sock.o -c sock.c

clean:
	rm -f *.o 2> /dev/null

distclean:	clean
	rm -f *~ 2> /dev/null