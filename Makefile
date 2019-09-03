all: options.exe

options.exe: options.o
		gcc -o options.exe options.o

options.o: hello.c
		gcc -c options.c

clean:
		rm options.o options.exe