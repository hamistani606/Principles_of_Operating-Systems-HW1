shell: simpleShell.o
	g++ simpleShell.o -o shell

simpleShell.o: simpleShell.c
	g++ -c simpleShell.c

clean:
	rm *.o shell
