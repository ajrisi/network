all:	tcp.o udp.o sock.o dns.o misc.o
	ar rcs libnetwork.a tcp.o udp.o sock.o dns.o misc.o

tcp.o:	tcp.h tcp.c
	gcc -Wall -ansi -fPIC -o tcp.o -c tcp.c

udp.o:	udp.h udp.c
	gcc -Wall -ansi -fPIC -o udp.o -c udp.c

sock.o:	sock.h sock.c
	gcc -Wall -ansi -fPIC -o sock.o -c sock.c

#DNS is temporarily not ANSI, because for some reason, the getaddrinfo fails when doing ansi
dns.o: dns.h dns.c
	gcc -Wall -fPIC -o dns.o -c dns.c

misc.o:	misc.h misc.c
	gcc -Wall -ansi -fPIC -o misc.o -c misc.c

clean:
	rm -f libnetwork.a 2> /dev/null
	rm -f *.o 2> /dev/null

distclean:	clean
	rm -f *~ 2> /dev/null