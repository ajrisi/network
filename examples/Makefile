all: prefork_server daytime_client

prefork_server: prefork_server.c
	gcc -o prefork_server prefork_server.c -lnetwork -L../ -I../

daytime_client: daytime_client.c
	gcc -o daytime_client daytime_client.c -lnetwork -L../ -I../

clean:
	rm -f prefork_server 2> /dev/null
	rm -f daytime_client 2> /dev/null

distclean: clean
	rm -f *~ 2> /dev/null
