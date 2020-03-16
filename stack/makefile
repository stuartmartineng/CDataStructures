CC = gcc
CFLAGS  = -g -Wall

default: stack clean

stack:  test.o stack.o unity.o
	$(CC) $(CFLAGS) -o target/testStack testStack.o stack.o unity.o

stack.o:  src/stack.c include/stack.h 
	$(CC) $(CFLAGS) -Iinclude -c src/stack.c

test.o:  test/testStack.c ../unity/unity.h
	$(CC) $(CFLAGS) -Iinclude -I../unity -c test/testStack.c

unity.o: ../unity/unity.h
	$(CC) $(CFLAGS) -I../unity -c ../unity/unity.c 

clean: 
	$(RM) count *.o *~