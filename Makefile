INST_HEADERS= tcp.h udp.h sock.h dns.h misc.h

all:	tcp.o udp.o sock.o dns.o misc.o
	ar rcs libnetwork.a tcp.o udp.o sock.o dns.o misc.o

tcp.o:	tcp.h tcp.c
	gcc -ggdb -Wall -ansi -fPIC -o tcp.o -c tcp.c

udp.o:	udp.h udp.c
	gcc -ggdb -Wall -ansi -fPIC -o udp.o -c udp.c

sock.o:	sock.h sock.c
	gcc -ggdb -Wall -ansi -fPIC -o sock.o -c sock.c

#DNS is temporarily not ANSI, because for some reason, the getaddrinfo fails when doing ansi
dns.o: dns.h dns.c
	gcc -ggdb -Wall -fPIC -o dns.o -c dns.c

misc.o:	misc.h misc.c
	gcc -ggdb -Wall -ansi -fPIC -o misc.o -c misc.c

install:
	install -m 644 libnetwork.a /usr/lib/
	mkdir /usr/include/network
	install -m 644 $(INST_HEADERS) /usr/include/network

uninstall:
	rm /usr/lib/libnetwork.a
	cd /usr/include/network && rm $(INST_HEADERS)
clean:
	rm -f libnetwork.a 2> /dev/null
	rm -f *.o 2> /dev/null

distclean:	clean
	rm -f *~ 2> /dev/null