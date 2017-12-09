all: c.c
	gcc -o control control.c
	gcc -o client client.c

clean: control debug
	rm control debug

debugClient:
	gcc -o debug -g client.c

debugControl:
	gcc -o debug -g control.c

valgrind: debug
	valgrind ./debug

gdb: debug
	gdb ./debug
