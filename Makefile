all:	tcp.o udp.o sock.o misc.o
	ar rcs libnetwork.a tcp.o udp.o sock.o misc.o

tcp.o:	tcp.h tcp.c
	gcc -Wall -ansi -o tcp.o -c tcp.c

udp.o:	udp.h udp.c
	gcc -Wall -ansi -o udp.o -c udp.c

sock.o:	sock.h sock.c
	gcc -Wall -ansi -o sock.o -c sock.c

misc.o:	misc.h misc.c
	gcc -Wall -ansi -o misc.o -c misc.c

clean:
	rm -f libnetwork.a 2> /dev/null
	rm -f *.o 2> /dev/null

distclean:	clean
	rm -f *~ 2> /dev/null