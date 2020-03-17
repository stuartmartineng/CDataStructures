CC = gcc
CFLAGS  = -g -Wall

default: stack clean

stack:  test.o linkedList.o unity.o
	$(CC) $(CFLAGS) -o target/testLinkedList testLinkedList.o linkedList.o unity.o

linkedList.o:  src/linkedList.c include/linkedList.h 
	$(CC) $(CFLAGS) -Iinclude -c src/linkedList.c

test.o:  test/testLinkedList.c ../unity/unity.h
	$(CC) $(CFLAGS) -Iinclude -I../unity -c test/testLinkedList.c

unity.o: ../unity/unity.h
	$(CC) $(CFLAGS) -I../unity -c ../unity/unity.c 

clean: 
	$(RM) count *.o *~