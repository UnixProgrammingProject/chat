chat:	main.o chat.o chat.h
	gcc -o chat main.o chat.o chat.h
main.o: main.c
	gcc -c main.c
chat.o: chat.c
	gcc -c chat.c
clean:
	ipcrm -a
	rm -f chat main.o chat.o
	rm /tmp/hojun
	rm /tmp/dodo
