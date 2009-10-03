all:	tcp.o udp.o

tcp.o:	tcp.h tcp.c
	gcc -Wall -ansi -o tcp.o -c tcp.c

udp.o:	udp.h udp.c
	gcc -Wall -ansi -o ucp.o -c udp.c

clean:
	rm *.o 2> /dev/null; true

distclean:	clean
	rm *~ 2> /dev/null; true