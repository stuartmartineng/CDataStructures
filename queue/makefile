CC = gcc
CFLAGS  = -g -Wall

default: queue clean

queue:  test.o queue.o unity.o
	$(CC) $(CFLAGS) -o target/testQueue testQueue.o queue.o unity.o

queue.o:  src/queue.c include/queue.h 
	$(CC) $(CFLAGS) -Iinclude -c src/queue.c

test.o:  test/testQueue.c ../unity/unity.h
	$(CC) $(CFLAGS) -Iinclude -I../unity -c test/testQueue.c

unity.o: ../unity/unity.h
	$(CC) $(CFLAGS) -I../unity -c ../unity/unity.c 

clean: 
	$(RM) count *.o *~